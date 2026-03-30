public class Response {
    private String info;
    private String meg;
    private int confirmCode = -1;
    private int permission = -1;
    
    public Response() {
    }
    
    public Response(String info) {
        deserialize(info);
    }
    
    public Response(Response reps) {
        this.info = reps.info;
        this.meg = reps.meg;
        this.confirmCode = reps.confirmCode;
        this.permission = reps.permission;
    }
    
    public boolean serialize(StringBuffer out) {
        String json = JSONUtil.serializeObject(this);
        out.append(json);
        return true;
    }
    
    public boolean deserialize(String in) {
        if (in == null || in.isEmpty()) {
            return false;
        }
        try {
            JSONUtil.deserializeResponse(in, this);
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
    
    public String getInfo() {
        return info;
    }
    
    public void setInfo(String info) {
        this.info = info;
    }
    
    public String getMeg() {
        return meg;
    }
    
    public void setMeg(String meg) {
        this.meg = meg;
    }
    
    public int getConfirmCode() {
        return confirmCode;
    }
    
    public void setConfirmCode(int confirmCode) {
        this.confirmCode = confirmCode;
    }
    
    public int getPermission() {
        return permission;
    }
    
    public void setPermission(int permission) {
        this.permission = permission;
    }
}