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

    Crypto eth = new Crypto(400, 15, 'E');
    Crypto bit = new Crypto(4000, 100, 'B');

    Order a = new Order(true,40,eth);
    Order b = new Order(true,70,eth);
    Order c = new Order(true,20,eth);
    Order d = new Order(true,110,eth);

    OrderBook Ord = new OrderBook();
    Ord.addOrder(a);
    Ord.addOrder(b);
    Ord.addOrder(c);
    Ord.addOrder(d);

    Ord.orderList();
 }
}