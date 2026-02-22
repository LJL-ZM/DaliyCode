#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <errno.h>
#include <vector>
#include "log.hpp" 

const int MIN_SCORE = 0;       
const int MAX_SCORE = 100;     
const string BIN_FILE = "./store/student_bin.dat";   

extern Log lg;

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

public:
    // 构造
    StudentManager() {
        head = new (nothrow) Node();
        if (head == nullptr) {
            lg(FATAL, "Memory allocation failed! Program exit!");
            exit(MEMORY_ALLOC_FAILED);
        }
        
        head->prev = head;
        head->next = head;
        count = 0;
        lg(INFO, "Student manager module initialized successfully");
    }

    //析构
    ~StudentManager() {
        if (count > 0) {
            Node* p = head->next;
            while (p != head) {
                Node* q = p->next;
                delete p;
                p = q;
            }
        }
        delete head;
        lg(INFO, "Student manager resource released, total %d nodes freed", count);
    }

    //插入单个学生信息
    bool insertStudent(const Student& s) {
        //校验学号是否重复
        int idCheck = checkStudentId(s.id);
        if (idCheck != SUCCESS) {
            return false;
        }
        // 创建新节点
        Node* newNode = new (nothrow) Node(s);
        if (newNode == nullptr) {
            lg(ERROR, "Memory allocation failed, cannot add student: id [%s]", s.id.c_str());
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
        return true;
    }

    // 学号查询学生
    Student* findStudentById(const std::string& id) {
        Node* p = findNodeById(id);
        if (p == nullptr) {
            lg(INFO, "Student query failed: id [%s] not found", id.c_str());
        } else {
            lg(INFO, "Student query success: id [%s], name [%s], score [%.2f]", p->data.id.c_str(), p->data.name.c_str(), p->data.score);
        }
        return p ? &(p->data) : nullptr;
    }

    // 修改学生信息
    bool modifyStudent(const std::string& id, const std::string& newName, float newScore) {
        Student* s = findStudentById(id);
        if (s == nullptr) {
            lg(ERROR, "Student modify failed: id [%s] not found", id.c_str());
            return false;
        }
        // 修改姓名
        if (!newName.empty()) {
            s->name = newName;
        }
        // 修改成绩
        if (newScore != -1) {
            s->score = newScore;
        }
        // 保存到文件
        saveToBinFile(BIN_FILE);
        lg(INFO, "Student info modified successfully: id [%s], name [%s], score [%.2f]", s->id.c_str(), s->name.c_str(), s->score);
        return true;
    }

    // 删除学生信息
    bool deleteStudent(const std::string& id) {
        Node* delNode = findNodeById(id);
        if (delNode == nullptr) {
            lg(ERROR, "Student delete failed: id [%s] not found", id.c_str());
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
        return true;
    }

    // 清空所有学生
    bool clearAllStudents() {
        if (count == 0) {
            lg(WARN, "Clear students failed: no student info");
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
        return true;
    }

    // 按成绩排序
    bool sortByScore(int order = 0) {
        if (count <= 1) {
            lg(WARN, "Score sort failed: student count less than 2");
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
        return true;
    }

    // 按学号排序（0升序/1降序）
    bool sortById(int order = 0) {
        if (count <= 1) {
            lg(WARN, "ID sort failed: student count less than 2");
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
        return true;
    }

    // 成绩统计（输出参数返回结果）
    bool scoreStatistics(int& totalCount, float& avgScore, float& maxScore, 
                        float& minScore, int& excellent, int& fail) {
        if (count == 0) {
            lg(WARN, "Score statistics failed: no student info");
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
        return true;
    }

    // 获取所有学生
    vector<Student> getAllStudents() {
        vector<Student> res;
        Node* p = head->next;
        while (p != head) {
            res.push_back(p->data);
            p = p->next;
        }
        return res;
    }

    // 从二进制文件读取
    bool readFromBinFile(const std::string& store_filename = BIN_FILE) {
        FILE* fp = fopen(store_filename.c_str(), "rb");
        if (fp == nullptr) {
            lg(ERROR, "File open failed: [%s], err str:%s", store_filename.c_str(), strerror(errno));
            return false;
        }
        // 清空原有数据
        clearAllStudents();
        // 读取学生总数
        int readCount;
        fread(&readCount, sizeof(int), 1, fp);
        if (readCount <= 0) {
            lg(INFO, "No student data in file: [%s]", store_filename.c_str());
            fclose(fp);
            return true;
        }

        // 读取每个学生信息
        int successCount = 0;
        for (int i = 0; i < readCount; i++) {
            Student s;
            // 读取学号
            int idLen;
            fread(&idLen, sizeof(int), 1, fp);
            char* idBuf = new (nothrow) char[idLen + 1];
            if (idBuf == nullptr) {
                lg(ERROR, "Memory allocation failed, read student %d failed", i+1);
                continue;
            }
            fread(idBuf, sizeof(char), idLen, fp);
            idBuf[idLen] = '\0';
            s.id = idBuf;
            delete[] idBuf;
            // 读取姓名
            int nameLen;
            fread(&nameLen, sizeof(int), 1, fp);
            char* nameBuf = new (nothrow) char[nameLen + 1];
            if (nameBuf == nullptr) {
                lg(ERROR, "Memory allocation failed, read student %d failed", i+1);
                continue;
            }
            fread(nameBuf, sizeof(char), nameLen, fp);
            nameBuf[nameLen] = '\0';
            s.name = nameBuf;
            delete[] nameBuf;
            // 读取成绩
            fread(&s.score, sizeof(float), 1, fp);
            // 插入学生信息
            Node* newNode = new (nothrow) Node(s);
            if (newNode == nullptr) {
                lg(ERROR, "Memory allocation failed, read student %d failed", i+1);
                continue;
            }
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            count++;
            successCount++;
        }

        fclose(fp);

        lg(INFO, "Read from binary file completed: [%s], plan %d, success %d", 
           store_filename.c_str(), readCount, successCount);
        return true;
    }

    // 获取学生总数
    int getStudentCount() {
        return count;
    }
}Manager;