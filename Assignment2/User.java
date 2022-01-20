import java.util.Vector;
// Parent which will be inherited by the childern of Admin and Trader
class User{
    // every user has a username and password
    protected String username;
    protected String login;

    // constructer sets the username and password for the user
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
    // funciton prints out the users details
    public void printUser(){
        System.out.println("Username: "+username+"\nPassword: "+login+"\n");
    }
}
// definition of a Trader, inherits from the user class
class Trader extends User{
    // traders have a FIAT amount wait for approval and an vector of all their transactions
    boolean approved = false;
    double Fiat = 0;
    // vector holds a list of the id's of all the traders' orders
    public Vector<Integer> Transactions = new Vector<>();
    // function allows trader to add funds in his account
    public void addFiat(double amount){
        // if not approved waning is outputted
        if (approved==false){
            System.out.println("Trader not Approved");
            return;
        }
        Fiat += amount;
    }
    // super function calls constructor in parent User class
    public Trader(String username, String login){
        super(username, login);
    }
    Request_Approval Approval(){
        Request_Approval request = new Request_Approval();
        this.approved = request.approved;
        return request;
    } 
}
// Admin class is a child of User parent class
class Administrator extends User{
    // Administrator uses super to access parents' constructor
    public Administrator(String username, String login){
        super(username, login);
    }
    void approvalRequest(Request_Approval request, Trader requestedBy){
        if (request.approved == false){
            Approve(requestedBy);
            requestedBy.approved = true;
            request.approved = true;
        }
    }

    // Administrator approves the Traders' request in the UserManager
    void Approve(Trader requestedBy){
        if (UserManager.Traders.contains(requestedBy)==true){
            UserManager.Traders.remove(requestedBy);
            UserManager.TradersApproved.add(requestedBy);
        }
    }
}

// UserManager class
class UserManager{
    // contains two vectors, the first one with the unapproved traders
    // and the other with the approved traders
    public static Vector<Trader> Traders = new Vector<>();
    public static Vector<Trader> TradersApproved = new Vector<>();
    // function created a Trader from the UserManager
    // the Trader is added to the Traders Vector to await approval
    public Trader createTrader(String username,String login){
        Trader x = new Trader(username,login);
        Traders.add(x);
        return x;
    }
    // Administrator is created from the UserManager
    public Administrator createAdministrator(String username,String login){
        Administrator x = new Administrator(username,login);
        return x;
    }
}
