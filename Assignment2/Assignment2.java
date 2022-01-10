import java.util.Vector;

public class Assignment2{
 public static void main(String[] args) {
    // Administrator Peter= new Administrator("peter34", "admin");
    // Trader john = new Trader("cooljohn","amazo45");
    // Request_Approval request = john.Approval();
    // // john.approved = true;
    // // Peter.approvalRequest(request, john);
    // System.out.println(john.approved);

    UserManager um = new UserManager();
    Trader john = um.createTrader("cooljohn","amazo45");
    Administrator Peter= um.createAdministrator("peter34", "admin");
    Peter.Approve(john);
 }
}