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
}
class Trader extends User{

}
class Administrator extends User{

}

public class Assignment2{
 public static void main(String[] args) {
     System.out.println("helli");
 }
}