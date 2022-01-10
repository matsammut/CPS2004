import java.util.Vector;

public class Assignment2{
 public static void main(String[] args) {
    Administrator Peter= new Administrator("peter34", "admin");
    Trader john = new Trader("cooljohn","amazo45");
    Request_Approval request = john.Approval();
    Peter.approvalRequest(request, john);
    System.out.println(john.approved);
 }
}