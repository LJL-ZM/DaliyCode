// class Solution {
// public:
//     bool is_valid(string s){
//         stack<char> st;
//         for(auto ch : s){
//             if(ch != '(' && ch != ')'){
//                 continue;
//             }
//             if(ch == '('){
//                 st.push(ch);
//             }
//             else if(st.empty()){
//                 return false;
//             }
//             else{
//                 st.pop();
//             }
//         }
//         if(st.size()){
//             return false;
//         }
//         return true;
//     }
//     void bfs(string &s, vector<string>& vs){
//         queue<string> q;
//         q.push(s);
//         haved.insert(s);
//         int cur_cnt = 1, next_cnt = 0;
//         bool is_true = false;
//         while(q.size()){
//             if(is_true && cur_cnt == 0){
//                 return;
//             }
//             if(cur_cnt == 0){
//                 cur_cnt = next_cnt;
//                 next_cnt = 0;
//             }
//             string f = q.front(); q.pop();
//             cur_cnt--;
//             for(int i = 0; i < f.size(); i++){
//                 string tmp = f;
//                 if(f[i] == '(' || f[i] == ')'){
//                     tmp.erase(i, 1);
//                     if(haved.count(tmp)){
//                         continue;
//                     }
//                     haved.insert(tmp);
//                     if(is_valid(tmp)){
//                         is_true = true;
//                         vs.push_back(tmp);
//                     }
//                     q.push(tmp);
//                 }
//             }
//         }
//     }
//     vector<string> removeInvalidParentheses(string s) {
//         bool ret = false;
//         for(auto ch : s){
//             if(ch == '(' || ch == ')'){
//                 ret = true;
//             }
//         }
//         if(ret == false || is_valid(s)){
//             return vector<string>{s};
//         }
//         vector<string> vs;
//         bfs(s, vs);  
//         //vs.pop_back(); 
//         return vs;
//     }
//     unordered_set<string> haved;
// };


//class Solution {
//public:
//    bool is_valid(string s) {
//        stack<char> st;
//        for (auto ch : s) {
//            if (ch != '(' && ch != ')') continue;
//            if (ch == '(') st.push(ch);
//            else if (st.empty()) return false;
//            else st.pop();
//        }
//        return st.empty();
//    }
//
//    void bfs(string& s, vector<string>& vs) {
//        queue<string> q;
//        unordered_set<string> visited;
//        q.push(s);
//        visited.insert(s);
//
//        int cur_cnt = q.size();
//        int next_cnt = 0;
//        bool is_true = false;
//        unordered_set<string> res_set;
//
//        while (!q.empty()) {
//            string f = q.front();
//            q.pop();
//            cur_cnt--;
//            for (int i = 0; i < f.size(); i++) {
//                if (f[i] != '(' && f[i] != ')') continue;
//                string tmp = f;
//                tmp.erase(i, 1);
//                if (visited.count(tmp)) continue;
//                visited.insert(tmp);
//                if (is_valid(tmp)) {
//                    is_true = true;
//                    res_set.insert(tmp);
//                }
//                q.push(tmp);
//                next_cnt++;
//            }
//            if (cur_cnt == 0) {
//                if (is_true) {
//                    vs.assign(res_set.begin(), res_set.end());
//                    return;
//                }
//                cur_cnt = next_cnt;
//                next_cnt = 0;
//            }
//        }
//    }
//
//    vector<string> removeInvalidParentheses(string s) {
//        if (is_valid(s)) {
//            return { s };
//        }
//        vector<string> vs;
//        bfs(s, vs);
//        if (vs.empty()) {
//            return { "" };
//        }
//        return vs;
//    }
//};