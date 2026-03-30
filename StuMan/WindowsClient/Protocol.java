public class Protocol {
    // Protocol separator
    public static final char PROTOCOL_SEM = '\n';
    
    // Operation type definitions
    public static final int OP_ADD_STUDENT = 1;   // Add student
    public static final int OP_DEL_STUDENT = 2;   // Delete student
    public static final int OP_MOD_STUDENT = 3;   // Modify student
    public static final int OP_QUERY_STUDENT = 4; // Query by ID
    public static final int OP_GET_ALL = 5;       // Get all students
    public static final int OP_SORT_SCORE = 6;    // Sort by score
    public static final int OP_SORT_ID = 7;       // Sort by ID
    public static final int OP_STATISTIC = 8;     // Score statistics
    public static final int OP_CLEAR_ALL = 9;     // Clear all
    public static final int OP_REGISTER = 12;     // Register
    public static final int OP_LOGIN = 13;        // Login
    
    // Role definitions
    public static final int ROLE_STU = 1;         // Student
    public static final int ROLE_TEA = 2;         // Teacher
    public static final int ROLE_MAN = 3;         // Manager
    
    // Safe string to integer conversion
    public static int safeStoi(String s) {
        if (s == null || s.isEmpty()) {
            return -1;
        }
        for (char c : s.toCharArray()) {
            if (!Character.isDigit(c)) {
                return -1;
            }
        }
        try {
            return Integer.parseInt(s);
        } catch (NumberFormatException e) {
            System.out.println("String to integer exception!");
            return -1;
        }
    }
    
    // Encode
    public static void encode(StringBuffer info, StringBuffer packageBuffer) {
        String infoStr = info.toString();
        packageBuffer.append(infoStr.length());
        packageBuffer.append(PROTOCOL_SEM);
        packageBuffer.append(infoStr);
        packageBuffer.append(PROTOCOL_SEM);
    }
    
    // Decode
    public static boolean decode(StringBuffer packageBuffer, StringBuffer infoBuffer) {
        String packageStr = packageBuffer.toString();
        int pos = packageStr.indexOf(PROTOCOL_SEM);
        if (pos == -1) {
            return false;
        }
        String lenStr = packageStr.substring(0, pos);
        int len = safeStoi(lenStr);
        if (len <= 0 || len + lenStr.length() + 2 > packageStr.length()) {
            return false;
        }
        infoBuffer.append(packageStr.substring(pos + 1, pos + 1 + len));
        packageBuffer.delete(0, len + lenStr.length() + 2);
        return true;
    }
}