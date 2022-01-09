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
    public Trader(String username, String login){
        super(username, login);
    }
}
class Administrator extends User{
    public Administrator(String username, String login){
        super(username, login);
    }
}

public class Assignment2{
 public static void main(String[] args) {
     System.out.println("helli");
 }
}