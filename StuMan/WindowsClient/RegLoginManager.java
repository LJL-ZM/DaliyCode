import java.util.Scanner;

public class RegLoginManager {
    private static final String KEY = "i am manager";
    
    public static void menuOpRegistAndLogin() {
        System.out.println("*****************************************************************");
        System.out.println("****      please chose a op, user_regist or user_login?      ****");
        System.out.println("****    12 : user_regist                  13 : user_login    ****");
        System.out.println("*****************************************************************");
    }
    
    public static void menuAboutRole() {
        System.out.println("*****************************************************************");
        System.out.println("****      please chose a role, teacher or student?           ****");
        System.out.println("****     1 : student                  2 : teacher            ****");
        System.out.println("*****************************************************************");
    }
    
    public static boolean checkUsername(StringBuffer name) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                String input = scanner.next();
                if (input.length() < 6 || input.length() > 18) {
                    System.out.println("Username length must be between 6-18 characters!");
                    continue;
                }
                for (char c : input.toCharArray()) {
                    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                        System.out.println("Username can only contain letters!");
                        continue;
                    }
                }
                name.append(input);
                return true;
            } catch (Exception e) {
                System.out.println("Input error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
    }
    
    public static boolean checkPassword(StringBuffer password) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                String input = scanner.next();
                if (input.length() < 6 || input.length() > 18) {
                    System.out.println("Password length must be between 6-18 characters!");
                    continue;
                }
                for (char c : input.toCharArray()) {
                    if (!Character.isDigit(c)) {
                        System.out.println("Password can only contain numbers!");
                        continue;
                    }
                }
                password.append(input);
                return true;
            } catch (Exception e) {
                System.out.println("Input error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
    }
    
    public static boolean checkRole(int[] role) {
        menuAboutRole();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                int input = scanner.nextInt();
                if (input != Protocol.ROLE_STU && input != Protocol.ROLE_TEA && input != Protocol.ROLE_MAN) {
                    System.out.println("Role error, please re-enter!");
                    continue;
                }
                role[0] = input;
                return true;
            } catch (Exception e) {
                System.out.println("Input error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
    }
    
    public static boolean checkMan(int role) {
        if (role == Protocol.ROLE_MAN) {
            System.out.print("If you are manager, please enter the key: ");
            Scanner scanner = new Scanner(System.in);
            String key = scanner.nextLine();
            if (!key.equals(KEY)) {
                System.out.println("Key error, you are not manager!");
                return false;
            }
        }
        return true;
    }
    
    public static boolean register() {
        StringBuffer name = new StringBuffer();
        StringBuffer password = new StringBuffer();
        int[] role = new int[1];
        
        System.out.println("Please enter your username, username length must be between 6-18 characters, only letters.");
        if (!checkUsername(name)) {
            System.out.println("Invalid username!");
            return false;
        }
        
        System.out.println("Please set a password, password length must be between 6-18 characters, only numbers.");
        if (!checkPassword(password)) {
            System.out.println("Invalid password!");
            return false;
        }
        
        System.out.println("Please enter your role");
        if (!checkRole(role)) {
            System.out.println("Invalid role!");
            return false;
        }
        
        if (!checkMan(role[0])) {
            System.out.println("You are not manager!");
            return false;
        }
        
        try {
            SocketManager socket = SocketManager.getSocket();
            SocketManager.creatAndSendReq(socket, name.toString(), password.toString(), String.valueOf(Protocol.OP_REGISTER), role[0]);
            
            StringBuffer packageBuffer = new StringBuffer();
            StringBuffer infoBuffer = new StringBuffer();
            boolean[] retCode = new boolean[1];
            Response reps = SocketManager.receiveAndDecode(socket, packageBuffer, infoBuffer, retCode);
            
            if (!retCode[0]) {
                socket.close();
                return false;
            }
            
            System.out.println(reps.getMeg());
            if (reps.getConfirmCode() != 1) {
                socket.close();
                return false;
            }
            
            socket.close();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    
    public static boolean login(int role) {
        StringBuffer name = new StringBuffer();
        StringBuffer password = new StringBuffer();
        
        System.out.println("Please enter your username, username length must be between 6-18 characters, only letters.");
        if (!checkUsername(name)) {
            System.out.println("Invalid username!");
            return false;
        }
        
        System.out.println("Please enter your password, password length must be between 6-18 characters, only numbers.");
        if (!checkPassword(password)) {
            System.out.println("Invalid password!");
            return false;
        }
        
        try {
            SocketManager socket = SocketManager.getSocket();
            SocketManager.creatAndSendReq(socket, name.toString(), password.toString(), String.valueOf(Protocol.OP_LOGIN), 0);
            
            StringBuffer packageBuffer = new StringBuffer();
            StringBuffer infoBuffer = new StringBuffer();
            boolean[] retCode = new boolean[1];
            Response reps = SocketManager.receiveAndDecode(socket, packageBuffer, infoBuffer, retCode);
            
            if (!retCode[0]) {
                socket.close();
                return false;
            }
            
            System.out.println(reps.getMeg());
            if (reps.getConfirmCode() != 1) {
                socket.close();
                return false;
            }
            
            role = reps.getPermission();
            socket.close();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}