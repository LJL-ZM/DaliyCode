//从 2000 年 1 月 1 日到 2026 年 4 月 12 日，一共有多少个既是星期一又是 1 号的日子？

//#include <iostream>
//using namespace std;
//int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//bool is_leap(int y) {
//	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
//}
//int main() {
//	int ret = 0;
//	int y = 2000, m = 1, d = 1, week = 6;
//	while (!(y == 2026 && m == 4 && d == 12)) {
//		//判断
//		if (week == 1 && d == 1) {
//			ret++;
//		}
//		//向后走一天
//		week++;
//		if (week > 7) {
//			week = 1;
//		}
//		d++;
//		//获取本月有几天
//		int month_day = days[m];
//		if (m == 2 && is_leap(y)) {
//			month_day++;
//		}
//		//逐级进位
//		if (d > month_day) {
//			d = 1;
//			m++;
//			if (m > 12) {
//				m = 1;
//				y++;
//			}
//		}
//	}
//	cout << ret << endl;
//
//
//
//
//	return 0;
//}


//#include <iostream>
//using namespace std;
//
//int gcd(int x, int y) {
//	return y == 0 ? x : gcd(y, x % y);
//}
//
//int lcm(int x, int y) {
//	return x / gcd(x, y) * y;
//}
//int main() {
//
//	cout << gcd(1000, 100) << endl;
//	cout << lcm(3, 4) << endl;
//
//
//	return 0;
//}



//#include <iostream>
//using namespace std;
//int days[] = {0, 31, 28, 31, 30 ,31, 30 ,31, 31, 30, 31, 30 , 31};
//
//bool is_leap(int y) {
//	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
//}
//
//int main() {
//	int ret = 0;
//	int d = 1, m = 1, y = 2000, week = 6;
//	while (true) {
//		if (13 == d && 5 == week) {
//			ret++;
//		}
//		if (ret == 2026) {
//			printf("%d%d%d%d%d", y, m / 10, m % 10, d / 10, d % 10);
//			break;
//		}
//		d++;
//		week = ((week + 1) % 7) == 0 ? 7 : ((week + 1) % 7);
//		int month_day = days[m];
//		if (is_leap(y) && m == 2) {
//			month_day++;
//		}
//		if (d > month_day) {
//			d = 1;
//			m++;
//			if (m > 12) {
//				m = 1;
//				y++;
//			}
//		}
//	}
//
//
//	return 0;
//}


//#include <iostream>
//using namespace std;
//int days[] = { 0, 31, 28, 31, 30 ,31, 30 ,31, 31, 30, 31, 30 , 31 };
//
//bool is_leap(int y) {
//	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
//}
//
//int main() {
//	int ret = 0;
//	int d = 1, m = 1, y = 2000, week = 6;
//	while (!(y == )) {
//		if (13 == d && 5 == week) {
//			ret++;
//		}
//		if (ret == 2026) {
//			printf("%d%d%d%d%d", y, m / 10, m % 10, d / 10, d % 10);
//			break;
//		}
//		d++;
//		week = ((week + 1) % 7) == 0 ? 7 : ((week + 1) % 7);
//		int month_day = days[m];
//		if (is_leap(y) && m == 2) {
//			month_day++;
//		}
//		if (d > month_day) {
//			d = 1;
//			m++;
//			if (m > 12) {
//				m = 1;
//				y++;
//			}
//		}
//	}
//
//
//	return 0;
//}



//排序！！！前缀和！！！差分！！！动态规划的优化+状态（位）dp！！

//#include <iostream>
//#include <set>
//using namespace std;
//typedef pair<int, int> PII;
//typedef long long LL;
//LL gcd(LL x, LL y) {
//	return y == 0 ? x : gcd(y, x % y);
//}
//LL lcm(LL x, LL y) {
//	return x / gcd(x, y) * y;
//}
//set<PII> m;
//int main() {
//	int ret = 0;
//	for (int i = 1; i <= 2026; i++) {
//		for (int j = 1; j <= 2026; j++) {
//			if (gcd(i, j) == 1 && lcm(i, j) == 2026 && m.count({i, j}) == 0) {
//				m.insert({i, j});
//				ret++;
//			}
//		}
//	}
//	cout << ret;
//
//
//	return 0;
//}



//#include <iostream>
//using namespace std;
//int main() {
//    int n; cin >> n;
//    string s; cin >> s;
//    for (int i = 1; i <= n; i++) {
//        int op; cin >> op;
//        switch (op) {
//        case 1: {
//            string s1; cin >> s1;
//            int pos = s.find(s1);
//            if (pos == string::npos) {
//                cout << -1 << endl;
//            }
//            else {
//                cout << pos << endl;
//            }
//            break;
//        }
//        case 2: {
//            string s1, s2; cin >> s1 >> s2;
//            int pos = s.find(s1);
//            if (pos == string::npos) {
//                cout << s << endl;
//            }
//            else {
//                s.replace(pos, s1.size(), s2);
//                cout << s << endl;
//            }
//            break;
//        }
//        case 3: {
//            string ch1, ch2, s2; cin >> ch1 >> ch2 >> s2;
//            string s1 = ch1 + ch2;
//            int pos = 0;
//            while (true) {
//                pos = s.find(s1, pos);
//                if (pos == string::npos) {
//                    break;
//                }
//                s.insert(pos + 1, s2);
//                pos += s2.size() + 1;
//            }
//            cout << s << endl;
//            break;
//        }
//        }
//    }
//
//
//
//    return 0;
//}



#include <iostream>
// #include <stack>
// using namespace std;
// int main(){
//     stack<int> st1;
//     stack<char> st2;
//     int n; cin >> n;
//     for(int i = 1; i <= n; i++){
//         int x; cin >> x;
//         st1.push(x);
//     }
//     for(int i = 1; i <= n - 1; i++){
//         char ch; cin >> ch;
//         st2.push(ch);
//     }
//     while(st1.size() != 1){
//         int x, y;
//         x = st1.top(); st1.pop();
//         y = st1.top(); st1.pop();
//         char op = st2.top(); st2.pop();
//         switch(op){
//             case '+':{
//                 st1.push(x + y);
//                 break;
//             }
//             case '-':{
//                 st1.push(y - x);
//                 break;
//             }
//             case '*':{
//                 st1.push(x * y);
//                 break;
//             }
//             case '/':{
//                 if(x == 0){
//                     cout << "ERROR: " << y << "/0";
//                     return 0;
//                 }
//                 st1.push(y / x);
//                 break;
//             }
//         }
//     }
//     cout << st1.top();

//     return 0;
// }




#include<iostream>
// #include <unordered_map>
// using namespace std;
// int main(){
//     int num = 0;
//     unordered_map<int, int> map;
//     int n; cin >> n;
//     for(int i = 1; i <= n; i++){
//         int x; char y; cin >> x >> y;
//         if(y == 'i'){
//             map[x] = 0;
//         }
//         else{
//             map[x] = 1;
//         }

//     }
//     int m; cin >> m;
//     //cout << m << endl;
//     for(int i = 1; i <= m; i++){
//         int cnt; cin >> cnt;
//         bool flag = true;
//         for(int j = 1; j <= cnt; j++){
//             int x; cin >> x;
//             if(map[x] == 1){
//                 flag = false;
//             }
//         }
//         if(flag){
//             num++;
//             if(num != 1){
//                 cout << ' ';
//             }
//             cout << i;
//         }
//     }
//     if(num == 0){
//         cout << "None";
//     }



//     return 0;
// }