import java.util.Scanner;

public class StuOpManager {
    private static final int ID_SIZE = 10;
    
    public static void menuOpStudent() {
        System.out.println("****************************************************************");
        System.out.println("****            please chose a op you will do               ****");
        System.out.println("**** 1 : add_student               2 : del_student_by_id    ****");
        System.out.println("**** 3 : mod_student_by_id         4 : find_student_by_id ******");
        System.out.println("**** 5 : get_all_student           6 : sort_students_by_score **");
        System.out.println("**** 7 : sort_students_by_id       8 : statistics_score ********");
        System.out.println("**** 9 : clear_all_students                                 ****");
        System.out.println("****    if you are student, you can not to do 1/2/3/9      *****");
        System.out.println("****    if you are teacher, you can not to do 9            *****");
        System.out.println("****************************************************************");
    }
    
    public static void menuOpSort() {
        System.out.println("****************************************************************");
        System.out.println("***** 0 : sort in ascending        1 : sort in decending    ****");
        System.out.println("****************************************************************");
    }
    
    public static boolean checkStuName(StringBuffer name) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                String input = scanner.next();
                if (input.isEmpty()) {
                    System.out.println("Name cannot be empty!");
                    continue;
                }
                for (char c : input.toCharArray()) {
                    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                        System.out.println("Name can only contain letters!");
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
    
    public static boolean checkStuScore(double[] score) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                double input = scanner.nextDouble();
                if (input < 0 || input > 100) {
                    System.out.println("Score must be between 0-100!");
                    continue;
                }
                score[0] = input;
                return true;
            } catch (Exception e) {
                System.out.println("Input error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
    }
    
    public static boolean checkStuId(StringBuffer id) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                String input = scanner.next();
                if (input.length() != ID_SIZE) {
                    System.out.println("ID length must be " + ID_SIZE + " digits!");
                    continue;
                }
                for (char c : input.toCharArray()) {
                    if (!Character.isDigit(c)) {
                        System.out.println("ID can only contain numbers!");
                        continue;
                    }
                }
                id.append(input);
                return true;
            } catch (Exception e) {
                System.out.println("Input error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
    }
    
    public static boolean stuOp(int role) {
        menuOpStudent();
        Scanner scanner = new Scanner(System.in);
        int opStu = -1;
        while (true) {
            try {
                opStu = scanner.nextInt();
                if (opStu < 1 || opStu > 9) {
                    System.out.println("Operation error, please enter a number between 1-9!");
                    continue;
                }
                break;
            } catch (Exception e) {
                System.out.println("Input error, please re-enter!");
                scanner.next(); // Clear invalid input
            }
        }
        
        double[] score = new double[1];
        StringBuffer order = new StringBuffer("-1");
        StringBuffer id = new StringBuffer();
        StringBuffer name = new StringBuffer();
        
        switch (opStu) {
            case 1: // Add student
                if (role == Protocol.ROLE_STU) {
                    System.out.println("You are student, permission denied!");
                    return false;
                }
                System.out.println("Please enter the student name to add, only letters");
                if (!checkStuName(name)) {
                    System.out.println("Invalid name!");
                    return false;
                }
                System.out.println("Please enter the student score to add, only 0-100");
                if (!checkStuScore(score)) {
                    System.out.println("Invalid score!");
                    return false;
                }
                System.out.println("Please enter the student ID to add, only numbers and length " + ID_SIZE + " digits");
                if (!checkStuId(id)) {
                    System.out.println("Invalid ID!");
                    return false;
                }
                break;
                
            case 2: // Delete student
                if (role == Protocol.ROLE_STU) {
                    System.out.println("You are student, permission denied!");
                    return false;
                }
                System.out.println("Please enter the student ID to delete");
                if (!checkStuId(id)) {
                    System.out.println("Invalid ID!");
                    return false;
                }
                break;
                
            case 3: // Modify student
                if (role == Protocol.ROLE_STU) {
                    System.out.println("You are student, permission denied!");
                    return false;
                }
                System.out.println("Please enter the student ID to modify");
                if (!checkStuId(id)) {
                    System.out.println("Invalid ID!");
                    return false;
                }
                System.out.println("Please enter the student name to modify");
                if (!checkStuName(name)) {
                    System.out.println("Invalid name!");
                    return false;
                }
                System.out.println("Please enter the student score to modify");
                if (!checkStuScore(score)) {
                    System.out.println("Invalid score!");
                    return false;
                }
                break;
                
            case 4: // Query student
                System.out.println("Please enter the student ID to query");
                if (!checkStuId(id)) {
                    System.out.println("Invalid ID!");
                    return false;
                }
                break;
                
            case 5: // Get all students
                for (int i = 1; i <= 5; i++) {
                    System.out.println("loading...");
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                break;
                
            case 6: // Sort by score
            case 7: // Sort by ID
                menuOpSort();
                int orderTmp = -1;
                while (true) {
                    try {
                        orderTmp = scanner.nextInt();
                        if (orderTmp != 0 && orderTmp != 1) {
                            System.out.println("Sort method error, please re-enter!");
                            continue;
                        }
                        order.append(orderTmp);
                        break;
                    } catch (Exception e) {
                        System.out.println("Input error, please re-enter!");
                        scanner.next(); // Clear invalid input
                    }
                }
                break;
                
            case 8: // Score statistics
                for (int i = 1; i <= 5; i++) {
                    System.out.println("loading...");
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                break;
                
            case 9: // Clear all students
                if (role == Protocol.ROLE_STU || role == Protocol.ROLE_TEA) {
                    System.out.println("You are not manager, permission denied!");
                    return false;
                }
                break;
        }
        
        try {
            SocketManager socket = SocketManager.getSocket();
            SocketManager.creatAndSendReq(socket, name.toString(), id.toString(), String.valueOf(opStu), score[0], order.toString());
            
            StringBuffer packageBuffer = new StringBuffer();
            StringBuffer infoBuffer = new StringBuffer();
            boolean[] retCode = new boolean[1];
            Response reps = SocketManager.receiveAndDecode(socket, packageBuffer, infoBuffer, retCode);
            
            if (!retCode[0]) {
                socket.close();
                return false;
            }
            
            System.out.println(reps.getMeg());
            System.out.println(reps.getInfo());
            socket.close();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}