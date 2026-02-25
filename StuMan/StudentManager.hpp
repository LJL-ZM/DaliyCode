#pragma once


#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <errno.h>
#include <vector>
#include <pthread.h>
#include "log.hpp" 




const int MIN_SCORE = 0;       
const int MAX_SCORE = 100;     
const string BIN_FILE = "./store/studentBin.dat";   


// 错误码枚举
enum ErrorCode {
    SUCCESS = 0,            // 成功
    ID_DUPLICATE = 1,       // 学号重复
    STUDENT_NOT_FOUND = 5,  // 学生未找到
    FILE_OPEN_FAILED = 6,   // 文件打开失败
    MEMORY_ALLOC_FAILED = 8 // 内存分配失败
};

// 学生数据
struct Student {
    Student(const std::string& id, const std::string& name, const float& score)
    :id(id)
    ,name(name)
    ,score(score)
    {}
    Student(const Student& st)
    :id(st.id)
    ,name(st.name)
    ,score(st.score)
    {}
    Student(){}
    string id;     
    string name;   
    float score;   
};

// 链表节点
struct Node {
    Student data;  
    Node* prev;    
    Node* next;   
    Node() : prev(nullptr), next(nullptr) {}
    Node(const Student& s) : data(s), prev(nullptr), next(nullptr) {}
};

//管理逻辑
class StudentManager {
private:
    Node* head;          
    int count;   
    pthread_mutex_t _mutex;
    static pthread_mutex_t _static_creat_mutex;
    static StudentManager* _ptr;
    bool _is_init;
    // 根据学号查找节点
    Node* findNodeById(const std::string& id) {
        if (count == 0) return nullptr;
        
        Node* p = head->next;
        while (p != head) {
            if (p->data.id == id) {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    //校验学号是否重复
    int checkStudentId(const std::string& id) {
        if (findNodeById(id) != nullptr) {
            lg(WARN, "Student id check failed: id [%s] already exists", id.c_str());
            return ID_DUPLICATE;
        }
        return SUCCESS;
    }

    // 保存到二进制文件
    bool saveToBinFile(const std::string& store_filename = BIN_FILE) {
        FILE* fp = fopen(store_filename.c_str(), "wb");
        if (fp == nullptr) {
            lg(ERROR, "File open failed: [%s], err str:%s", store_filename.c_str(), strerror(errno));
            return false;
        }
        // 写入学生总数
        fwrite(&count, sizeof(int), 1, fp);
        // 遍历写入每个学生信息
        Node* p = head->next;
        while (p != head) {
            int idLen = p->data.id.length();
            fwrite(&idLen, sizeof(int), 1, fp);
            fwrite(p->data.id.c_str(), sizeof(char), idLen, fp);
            int nameLen = p->data.name.length();
            fwrite(&nameLen, sizeof(int), 1, fp);
            fwrite(p->data.name.c_str(), sizeof(char), nameLen, fp);
            fwrite(&p->data.score, sizeof(float), 1, fp);
            p = p->next;
        }
        fclose(fp);
        lg(INFO, "Saved %d students to binary file: [%s]", count, store_filename.c_str());
        return true;
    }
    void clearAllStudentsUnlocked() {
        if (count > 0) {
            Node* p = head->next;
            while (p != head) {
                Node* q = p->next;
                delete p;
                p = q;
            }
        }
        head->prev = head;
        head->next = head;
        count = 0;
    }
    // 构造
    StudentManager() 
    :_is_init(false)//未初始化
    {
        head = new (nothrow) Node();
        if (head == nullptr) {
            lg(FATAL, "Memory allocation failed! Program exit!");
            exit(MEMORY_ALLOC_FAILED);
        }
        
        head->prev = head;
        head->next = head;
        count = 0;
    }
    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;
public:
    void Init(const std::string& store_filename = BIN_FILE){
        if(_is_init){
            return;
        }
        //初始化锁
        pthread_mutex_lock(&_static_creat_mutex);
        if(_is_init){
            pthread_mutex_unlock(&_static_creat_mutex);
            return;
        }
        pthread_mutex_init(&_mutex, NULL);
        lg(INFO, "Student manager module initialized successfully");
        //初始化文件及内容
        FILE* fd = fopen(store_filename.c_str(), "ab");
        if(fd == nullptr){
            lg(FATAL, "file [%s] init err : %s", store_filename.c_str(), strerror(errno));
            exit(FILE_OPEN_FAILED);
        }
        fclose(fd);
        if(!readFromBinFile()){
            lg(ERROR, "file [%s] read err : %s", store_filename.c_str(), strerror(errno));
        }
        _is_init = true;
        pthread_mutex_unlock(&_static_creat_mutex);
    }
    static StudentManager& getInstance(){
        if(_ptr == nullptr){
            pthread_mutex_lock(&_static_creat_mutex);
            if(_ptr == nullptr){
                _ptr = new StudentManager();
            }
            pthread_mutex_unlock(&_static_creat_mutex);
        }
        return *_ptr;
    }
    //析构
    ~StudentManager() {
        pthread_mutex_lock(&_mutex);
        if (count > 0) {
            Node* p = head->next;
            while (p != head) {
                Node* q = p->next;
                delete p;
                p = q;
            }
        }
        delete head;
        pthread_mutex_unlock(&_mutex);
        pthread_mutex_destroy(&_mutex);
        lg(INFO, "Student manager resource released, total %d nodes freed", count);
    }

    //插入单个学生信息
    bool insertStudent(const Student& s) {
        pthread_mutex_lock(&_mutex);
        //校验学号是否重复
        int idCheck = checkStudentId(s.id);
        if (idCheck != SUCCESS) {
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        // 创建新节点
        Node* newNode = new (nothrow) Node(s);
        if (newNode == nullptr) {
            lg(ERROR, "Memory allocation failed, cannot add student: id [%s]", s.id.c_str());
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        // 插入
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        count++;      
        // 保存到文件
        saveToBinFile(BIN_FILE);

        lg(INFO, "Student info inserted successfully: id [%s], name [%s], score [%.2f]", s.id.c_str(), s.name.c_str(), s.score);
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 学号查询学生
    Student* findStudentById(const std::string& id) {
        pthread_mutex_lock(&_mutex);
        Node* p = findNodeById(id);
        if (p == nullptr) {
            lg(INFO, "Student query failed: id [%s] not found", id.c_str());
        } else {
            lg(INFO, "Student query success: id [%s], name [%s], score [%.2f]", p->data.id.c_str(), p->data.name.c_str(), p->data.score);
        }
        Student* ret = p ? &(p->data) : nullptr;
        pthread_mutex_unlock(&_mutex);
        return ret;
    }

    // 修改学生信息
    bool modifyStudent(const std::string& id, const std::string& newName, float newScore) {
        //std::cout << id << ' ' << newName << ' ' << newScore << std::endl;
        pthread_mutex_lock(&_mutex);
        //Student* s = findStudentById(id);
        Student* s = &((findNodeById(id))->data);
        if (s == nullptr) {
            lg(ERROR, "Student modify failed: id [%s] not found", id.c_str());
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        //std::cout << "ptr != nullptr" << std::endl;
        // 修改姓名
        if (!newName.empty()) {
            s->name = newName;
        }
        //std::cout << "name mv success" << std::endl;
        // 修改成绩
        if (newScore != -1) {
            s->score = newScore;
        }
        //std::cout << "score mv success" << std::endl;
        // 保存到文件
        saveToBinFile(BIN_FILE);
        lg(INFO, "Student info modified successfully: id [%s], name [%s], score [%.2f]", s->id.c_str(), s->name.c_str(), s->score);
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 删除学生信息
    bool deleteStudent(const std::string& id) {
        pthread_mutex_lock(&_mutex);
        Node* delNode = findNodeById(id);
        if (delNode == nullptr) {
            lg(ERROR, "Student delete failed: id [%s] not found", id.c_str());
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        Node* prevNode = delNode->prev;
        Node* nextNode = delNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        delete delNode;
        count--;
        // 保存
        saveToBinFile(BIN_FILE);
        lg(INFO, "Student deleted successfully: id [%s], remaining count: %d", id.c_str(), count);
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 清空所有学生
    bool clearAllStudents() {
        pthread_mutex_lock(&_mutex);
        if (count == 0) {
            lg(WARN, "Clear students failed: no student info");
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        // 释放所有数据节点
        Node* p = head->next;
        while (p != head) {
            Node* q = p->next;
            delete p;
            p = q;
        }
        // 恢复头节点自循环
        head->prev = head;
        head->next = head;
        int delCount = count;
        count = 0;
        // 保存到文件
        saveToBinFile(BIN_FILE);
        lg(INFO, "All students cleared! Total %d students deleted", delCount);
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 按成绩排序
    bool sortByScore(int order = 0) {
        pthread_mutex_lock(&_mutex);
        if (count <= 1) {
            lg(WARN, "Score sort failed: student count less than 2");
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        // 冒泡排序
        for (int i = 0; i < count - 1; i++) {
            Node* p = head->next;
            Node* q = p->next;
            for (int j = 0; j < count - 1 - i; j++) {
                bool needSwap = false;
                if (order == 0) {
                    needSwap = (p->data.score > q->data.score);
                } else {
                    needSwap = (p->data.score < q->data.score);
                }
                if (needSwap) {
                    // 交换节点数据
                    Student temp = p->data;
                    p->data = q->data;
                    q->data = temp;
                }
                p = q;
                q = q->next;
            }
        }
        //保存
        saveToBinFile(BIN_FILE);
        lg(INFO, "Score sort completed: %s order", order == 0 ? "ascending" : "descending");
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 按学号排序（0升序/1降序）
    bool sortById(int order = 0) {
        pthread_mutex_lock(&_mutex);
        if (count <= 1) {
            lg(WARN, "ID sort failed: student count less than 2");
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        // 冒泡排序
        for (int i = 0; i < count - 1; i++) {
            Node* p = head->next;
            Node* q = p->next;
            for (int j = 0; j < count - 1 - i; j++) {
                bool needSwap = false;
                if (order == 0) {
                    needSwap = (p->data.id > q->data.id);
                } else {
                    needSwap = (p->data.id < q->data.id);
                }

                if (needSwap) {
                    // 交换节点数据
                    Student temp = p->data;
                    p->data = q->data;
                    q->data = temp;
                }
                p = q;
                q = q->next;
            }
        }
        // 保存
        saveToBinFile(BIN_FILE);
        lg(INFO, "ID sort completed: %s order", order == 0 ? "ascending" : "descending");
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 成绩统计
    bool scoreStatistics(int& totalCount, float& avgScore, float& maxScore, 
                        float& minScore, int& excellent, int& fail) {
        pthread_mutex_lock(&_mutex);
        if (count == 0) {
            lg(WARN, "Score statistics failed: no student info");
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        // 初始化
        float totalScore = 0.0f;
        maxScore = MIN_SCORE;
        minScore = MAX_SCORE;
        excellent = 0;
        fail = 0;
        //统计
        Node* p = head->next;
        while (p != head) {
            float score = p->data.score;
            totalScore += score;
            if (score > maxScore) maxScore = score;
            if (score < minScore) minScore = score;
            // 成绩分段统计
            if (score >= 90) {
                excellent++;
            } else if (score < 60) {
                fail++;
            }
            p = p->next;
        }

        // 计算输出参数
        totalCount = count;
        avgScore = totalScore / count;

        lg(INFO, "Score statistics completed: total %d, avg %.2f, max %.2f, min %.2f, excellent %d, fail %d",
           totalCount, avgScore, maxScore, minScore, excellent, fail);
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 获取所有学生
    vector<Student> getAllStudents() {
        pthread_mutex_lock(&_mutex);
        vector<Student> res;
        Node* p = head->next;
        while (p != head) {
            res.push_back(p->data);
            p = p->next;
        }
        pthread_mutex_unlock(&_mutex);
        return res;
    }

    // 从二进制文件读取
    bool readFromBinFile(const std::string& store_filename = BIN_FILE) {
        pthread_mutex_lock(&_mutex);
        if (access(store_filename.c_str(), F_OK) != 0) {
            lg(WARN, "file not exist, create new: %s", store_filename.c_str()); 
            FILE* fp = fopen(store_filename.c_str(), "wb");
            if (fp == nullptr) {
                lg(FATAL, "create new file fail: %s", strerror(errno));
                pthread_mutex_unlock(&_mutex);
                return false;
            }
            int zero_count = 0;
            fwrite(&zero_count, sizeof(int), 1, fp);
            fclose(fp);
            _is_init = true; // 初始化完成
            pthread_mutex_unlock(&_mutex);
            return true;
        }
        FILE* fp = fopen(store_filename.c_str(), "rb");
        if (fp == nullptr) {
            lg(FATAL, "open file fail for read: %s", strerror(errno));
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        int readCount = 0;
        size_t fread_ret = fread(&readCount, sizeof(int), 1, fp);
        if (readCount > 10000) {
            lg(FATAL, "invalid student count:%d (read ret:%u)", readCount, fread_ret);
            fclose(fp);
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        clearAllStudentsUnlocked();    
        for (int i = 0; i < readCount; ++i) {
        Student s;
        int idLen = 0, nameLen = 0;
        if (fread(&idLen, sizeof(int), 1, fp) != 1 || idLen <= 0 || idLen >= 64) {
            lg(ERROR, "read id len fail for student %d", i+1);
            break; // 数据不对
        }
        char id_buf[64] = {0};
        if (fread(id_buf, 1, idLen, fp) != idLen) {
            lg(ERROR, "read id fail for student %d", i+1);
            break;
        }
        s.id = std::string(id_buf, idLen);

        // 读取姓名长度
        if (fread(&nameLen, sizeof(int), 1, fp) != 1 || nameLen <= 0 || nameLen >= 64) {
            lg(ERROR, "read name len fail for student %d", i+1);
            break;
        }
        char name_buf[64] = {0};
        if (fread(name_buf, 1, nameLen, fp) != nameLen) {
            lg(ERROR, "read name fail for student %d", i+1);
            break;
        }
        s.name = std::string(name_buf, nameLen);
        // 读取成绩
        if (fread(&s.score, sizeof(float), 1, fp) != 1) {
            lg(ERROR, "read score fail for student %d", i+1);
            break;
        }
        Node* newNode = new (nothrow) Node(s);
        if (newNode == nullptr) {
            lg(ERROR, "memory alloc fail for student %d", i+1);
            break;
        }
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        count++;
    }
        fclose(fp);
        lg(INFO, "load %d students success", count);
        pthread_mutex_unlock(&_mutex);
        return true;
    }

    // 获取学生总数
    int getStudentCount() {
        pthread_mutex_lock(&_mutex);
        int c = count;
        pthread_mutex_unlock(&_mutex);
        return c;
    }
};
pthread_mutex_t StudentManager::_static_creat_mutex = PTHREAD_MUTEX_INITIALIZER;
StudentManager* StudentManager::_ptr = nullptr;

#define Manager StudentManager::getInstance()

