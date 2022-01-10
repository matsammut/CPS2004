import java.util.Vector;
class UserManager{
    private static Vector<Trader> Traders = new Vector<>();
    private static Vector<Administrator> Admins = new Vector<>();
    public Trader createTrader(String username,String login){
        Trader x = new Trader(username,login);
        Traders.add(x);
        return x;
    }
    public Administrator createAdministrator(String username,String login){
        Administrator x = new Administrator(username,login);
        Admins.add(x);
        return x;
    }
    public void Approve(Trader x){
        if (Traders.contains(x) == true){

        }
        return;
    }
}
class User{
    protected String username;
    protected String login;

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
    }
    
}
class Administrator extends User{
    public Administrator(String username, String login){
        super(username, login);
    }
    public boolean approvalRequest(boolean approval, String login){
        x.approved = approval;
    }
}

public class Assignment2{
 public static void main(String[] args) {
    Administrator Peter= new Administrator("peter34", "admin");
    System.out.println(Peter.login);
 }
}