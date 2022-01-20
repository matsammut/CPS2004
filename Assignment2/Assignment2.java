// main class used simply for testing purposes
public class Assignment2{
 public static void main(String[] args) {
    UserManager um = new UserManager();
    Trader john = um.createTrader("cooljohn","amazo45");
    Administrator Peter= um.createAdministrator("peter34", "admin");

    Peter.Approve(john);
    Peter.approvalRequest(john.Approval(), john);

    Crypto eth = new Crypto(400, 15, 'E');
    Crypto bit = new Crypto(4000, 100, 'B');

    OrderBook Ord = new OrderBook();
    
    Ord.addOrder(john,true,40,eth);
    Ord.addOrder(john,false,20,eth);
    Ord.addOrder(john,true,30,bit);
    Ord.addOrder(john,true,110,eth);
    Ord.printOrders();

    Ord.matchEngine();
    Ord.CancelOrder(john,0);
    Ord.printOrders();
    Ord.ViewTradersOrders(john);
    
 }
}