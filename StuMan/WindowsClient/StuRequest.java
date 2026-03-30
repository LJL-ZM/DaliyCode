public class StuRequest extends BaseRequest {
    private String order;
    private String name;
    private String id;
    private double score;
    
    public StuRequest() {
    }
    
    public StuRequest(String opType, String order, String name, String id, double score) {
        this.opType = opType;
        this.order = order;
        this.name = name;
        this.id = id;
        this.score = score;
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
            JSONUtil.deserializeStuRequest(in, this);
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
    
    public String getOrder() {
        return order;
    }
    
    public void setOrder(String order) {
        this.order = order;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public String getId() {
        return id;
    }
    
    public void setId(String id) {
        this.id = id;
    }
    
    public double getScore() {
        return score;
    }
    
    public void setScore(double score) {
        this.score = score;
    }
}