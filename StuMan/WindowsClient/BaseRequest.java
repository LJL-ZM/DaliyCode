public abstract class BaseRequest {
    protected String opType;
    
    public abstract boolean serialize(StringBuffer out);
    public abstract boolean deserialize(String in);
    public abstract int getOp();
    
    public String getOpType() {
        return opType;
    }
    
    public void setOpType(String opType) {
        this.opType = opType;
    }
}