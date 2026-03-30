public class JSONUtil {
    // Simple JSON serialization method
    public static String serializeObject(Object obj) {
        if (obj instanceof StuRequest) {
            StuRequest req = (StuRequest) obj;
            StringBuilder sb = new StringBuilder();
            sb.append("{");
            sb.append("\"_op_type\":\"").append(req.getOpType()).append("\",");
            sb.append("\"_name\":\"").append(req.getName()).append("\",");
            sb.append("\"_id\":\"").append(req.getId()).append("\",");
            sb.append("\"_order\":\"").append(req.getOrder()).append("\",");
            sb.append("\"_score\":").append(req.getScore());
            sb.append("}");
            return sb.toString();
        } else if (obj instanceof RegLoginRequest) {
            RegLoginRequest req = (RegLoginRequest) obj;
            StringBuilder sb = new StringBuilder();
            sb.append("{");
            sb.append("\"_ip\":\"").append(req.getIp()).append("\",");
            sb.append("\"_user_name\":\"").append(req.getUserName()).append("\",");
            sb.append("\"_password\":\"").append(req.getPassword()).append("\",");
            sb.append("\"_role\":\"").append(req.getRole()).append("\",");
            sb.append("\"_op_type\":\"").append(req.getOpType()).append("\"");
            sb.append("}");
            return sb.toString();
        } else if (obj instanceof Response) {
            Response resp = (Response) obj;
            StringBuilder sb = new StringBuilder();
            sb.append("{");
            sb.append("\"_info\":\"").append(resp.getInfo()).append("\",");
            sb.append("\"_meg\":\"").append(resp.getMeg()).append("\",");
            sb.append("\"_confirm_code\":").append(resp.getConfirmCode()).append(",");
            sb.append("\"_permission\":").append(resp.getPermission());
            sb.append("}");
            return sb.toString();
        }
        return "{}";
    }
    
    // Simple JSON deserialization method
    public static void deserializeStuRequest(String json, StuRequest req) {
        try {
            // Simple parse JSON string
            json = json.substring(1, json.length() - 1); // Remove {} 
            String[] pairs = json.split(",");
            for (String pair : pairs) {
                String[] keyValue = pair.split(":");
                if (keyValue.length != 2) continue;
                String key = keyValue[0].trim().replace("\"", "");
                String value = keyValue[1].trim();
                
                switch (key) {
                    case "_op_type":
                        req.setOpType(value.replace("\"", ""));
                        break;
                    case "_name":
                        req.setName(value.replace("\"", ""));
                        break;
                    case "_id":
                        req.setId(value.replace("\"", ""));
                        break;
                    case "_order":
                        req.setOrder(value.replace("\"", ""));
                        break;
                    case "_score":
                        req.setScore(Double.parseDouble(value));
                        break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void deserializeRegLoginRequest(String json, RegLoginRequest req) {
        try {
            // Simple parse JSON string
            json = json.substring(1, json.length() - 1); // Remove {} 
            String[] pairs = json.split(",");
            for (String pair : pairs) {
                String[] keyValue = pair.split(":");
                if (keyValue.length != 2) continue;
                String key = keyValue[0].trim().replace("\"", "");
                String value = keyValue[1].trim();
                
                switch (key) {
                    case "_ip":
                        req.setIp(value.replace("\"", ""));
                        break;
                    case "_user_name":
                        req.setUserName(value.replace("\"", ""));
                        break;
                    case "_password":
                        req.setPassword(value.replace("\"", ""));
                        break;
                    case "_role":
                        req.setRole(value.replace("\"", ""));
                        break;
                    case "_op_type":
                        req.setOpType(value.replace("\"", ""));
                        break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void deserializeResponse(String json, Response resp) {
        try {
            // Simple parse JSON string
            json = json.substring(1, json.length() - 1); // Remove {} 
            String[] pairs = json.split(",");
            for (String pair : pairs) {
                String[] keyValue = pair.split(":");
                if (keyValue.length != 2) continue;
                String key = keyValue[0].trim().replace("\"", "");
                String value = keyValue[1].trim();
                
                switch (key) {
                    case "_info":
                        resp.setInfo(value.replace("\"", ""));
                        break;
                    case "_meg":
                        resp.setMeg(value.replace("\"", ""));
                        break;
                    case "_confirm_code":
                        resp.setConfirmCode(Integer.parseInt(value));
                        break;
                    case "_permission":
                        resp.setPermission(Integer.parseInt(value));
                        break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}