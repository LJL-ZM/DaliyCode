import java.io.*;
import java.net.*;

public class SocketManager {
    private static final String SERVER_IP = "43.138.32.230";
    private static final int SERVER_PORT = 8888;
    
    private Socket socket;
    private OutputStream outputStream;
    private InputStream inputStream;
    
    public SocketManager() {
        this.socket = null;
        this.outputStream = null;
        this.inputStream = null;
    }
    
    public void connect() throws IOException {
        socket = new Socket(SERVER_IP, SERVER_PORT);
        outputStream = socket.getOutputStream();
        inputStream = socket.getInputStream();
    }
    
    public boolean write(String info) throws IOException {
        if (socket == null || !socket.isConnected()) {
            return false;
        }
        
        byte[] data = info.getBytes();
        outputStream.write(data);
        outputStream.flush();
        return true;
    }
    
    public String readAll() throws IOException {
        if (socket == null || !socket.isConnected()) {
            return null;
        }
        
        StringBuilder sb = new StringBuilder();
        byte[] buffer = new byte[10240];
        int bytesRead;
        
        while ((bytesRead = inputStream.read(buffer)) != -1) {
            sb.append(new String(buffer, 0, bytesRead));
            if (sb.indexOf(String.valueOf(Protocol.PROTOCOL_SEM)) != -1) {
                break;
            }
        }
        
        return sb.toString();
    }
    
    public void close() {
        try {
            if (inputStream != null) {
                inputStream.close();
            }
            if (outputStream != null) {
                outputStream.close();
            }
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public boolean isValid() {
        return socket != null && socket.isConnected() && !socket.isClosed();
    }
    
    public static SocketManager getSocket() throws IOException {
        SocketManager socketManager = new SocketManager();
        socketManager.connect();
        return socketManager;
    }
    
    public static Response receiveAndDecode(SocketManager socket, StringBuffer packageBuffer, StringBuffer infoBuffer, boolean[] retCode) {
        retCode[0] = false;
        packageBuffer.setLength(0);
        infoBuffer.setLength(0);
        
        try {
            String packageStr = socket.readAll();
            if (packageStr == null || packageStr.isEmpty()) {
                System.out.println("读取失败");
                socket.close();
                return new Response();
            }
            
            packageBuffer.append(packageStr);
            if (!Protocol.decode(packageBuffer, infoBuffer)) {
                System.out.println("响应错误");
            } else {
                retCode[0] = true;
            }
            
            return new Response(infoBuffer.toString());
        } catch (IOException e) {
            e.printStackTrace();
            socket.close();
            return new Response();
        }
    }
    
    public static void creatAndSendReq(SocketManager socket, String userName, String password, String opType, int role) throws IOException {
        RegLoginRequest req = new RegLoginRequest(userName, password, role, opType);
        StringBuffer info = new StringBuffer();
        StringBuffer packageBuffer = new StringBuffer();
        req.serialize(info);
        Protocol.encode(info, packageBuffer);
        socket.write(packageBuffer.toString());
    }
    
    public static void creatAndSendReq(SocketManager socket, String stuName, String id, String opType, double score, String order) throws IOException {
        StuRequest req = new StuRequest(opType, order, stuName, id, score);
        StringBuffer info = new StringBuffer();
        StringBuffer packageBuffer = new StringBuffer();
        req.serialize(info);
        Protocol.encode(info, packageBuffer);
        socket.write(packageBuffer.toString());
    }
}