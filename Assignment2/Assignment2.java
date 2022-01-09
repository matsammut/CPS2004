import java.util.Vector;
class ApprovalSheet{
    private static Vector<String> toApprove = new Vector<>();
    private static Vector<String> Approved = new Vector<>();
    public void approvalRequest(boolean approval, String login){
        toApprove.add(login);
    }
    public boolean checkApproved(String login){
        return Approved.contains(login);
    }
}
class User{
    String username;
    String login;

    public User(String username,String login){
        setUsername(username);
        setLogin(login);
    }

    public void setUsername(String username){
        this.username = username;
    }
    public void setLogin(String login){
        this.login = login;
    }

    public void printUser(){
        System.out.println("Username: "+username+"\nPassword: "+login+"\n");
    }
}
class Trader extends User{
    boolean approved = false;
    public Trader(String username, String login){
        super(username, login);
        approved = checkApproved(login);
    }
}
class Administrator extends User{
    public Administrator(String username, String login){
        super(username, login);
    }
    public boolean approvalRequest(boolean approval, String login){
        return true;
    }
    public 
}

public class Assignment2{
 public static void main(String[] args) {
    Administrator Peter= new Administrator("peter34", "admin");
    System.out.println(Peter.login);
 }
}