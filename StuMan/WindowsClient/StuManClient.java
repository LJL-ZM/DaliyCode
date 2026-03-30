import java.io.*;
import java.net.*;
import java.util.Scanner;

public class StuManClient {
    public static void main(String[] args) {
        try {
            // Initialize
            System.out.println("Student Information Management System Client");
            
            // Choose login/register
            int role = 0;
            while (true) {
                int rlOp = getOp();
                if (rlOp != Protocol.OP_REGISTER && rlOp != Protocol.OP_LOGIN) {
                    continue;
                }
                if (rlOp == Protocol.OP_REGISTER) {
                    // Register
                    boolean regRet = RegLoginManager.register();
                    if (!regRet) {
                        continue;
                    }
                    // Register success
                } else if (rlOp == Protocol.OP_LOGIN) {
                    // Login
                    boolean loginRet = RegLoginManager.login(role);
                    if (!loginRet) {
                        continue;
                    } else {
                        break;
                    }
                }
            }
            
            // Login success
            // Loop---print menu + local test permission + send request + read response + print result
            while (true) {
                StuOpManager.stuOp(role);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    private static int getOp() {
        RegLoginManager.menuOpRegistAndLogin();
        Scanner scanner = new Scanner(System.in);
        int op = -1;
        while (true) {
            try {
                op = scanner.nextInt();
                break;
            } catch (Exception e) {
                System.out.println("Operation error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
        return op;
    }
}