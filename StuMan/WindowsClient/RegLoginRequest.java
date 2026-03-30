public class RegLoginRequest extends BaseRequest {
    private String ip;
    private String userName;
    private String password;
    private String role;
    
    public RegLoginRequest() {
        this.role = "0";
    }
    
    public RegLoginRequest(String userName, String password, int role, String opType) {
        this.userName = userName;
        this.password = password;
        this.role = String.valueOf(role);
        this.opType = opType;
    }
    
    @Override
    public boolean serialize(StringBuffer out) {
        String json = JSONUtil.serializeObject(this);
        out.append(json);
        return true;
    }
    
    @Override
    public boolean deserialize(String in) {
        if (in == null || in.isEmpty()) {
            return false;
        }
        try {
            JSONUtil.deserializeRegLoginRequest(in, this);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    
    @Override
    public int getOp() {
        return Protocol.safeStoi(opType);
    }
    
    public String getIp() {
        return ip;
    }
    
    public void setIp(String ip) {
        this.ip = ip;
    }
    
    public String getUserName() {
        return userName;
    }
    
    public void setUserName(String userName) {
        this.userName = userName;
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
    
    public String getRole() {
        return role;
    }
    
    public void setRole(String role) {
        this.role = role;
    }
}