import java.util.Vector;
import java.util.Iterator;
class Order {
    int id;
    // false for buy

    boolean buySell;
    // false for market
    boolean marketLimit;
    int Quantity;
    int Filled;
    Crypto crypto;
    double bidAsk_price;
    
    public Order(int id, boolean buySell,int Quantity, Crypto crypto){
        this.id = id;
        this.buySell = buySell;
        this.marketLimit = false;
        this.Quantity = Quantity;
        this.Filled = 0;
        this.crypto = crypto;
        this.bidAsk_price = crypto.avgprice;
    }
    public Order(int id,boolean buySell,int Quantity, Crypto crypto, double bidAsk_price){
        this.id = id;
        this.buySell = buySell;
        this.marketLimit = true;
        this.Quantity = Quantity;
        this.Filled = 0;
        this.crypto = crypto;
        this.bidAsk_price = bidAsk_price;
    }

}

public class OrderBook{
    private static Vector<Order> Orders = new Vector<>();
    private int id = 0;
    void addOrder(boolean buySell,int Quantity, Crypto crypto)    
    {
        Order ordered = new Order(id,buySell,Quantity,crypto);
        Orders.add(ordered);
        id++;
    }
    void addOrder(boolean buySell,int Quantity, Crypto crypto, double bidAsk_price)    
    {
        Order ordered = new Order(id,buySell,Quantity,crypto,bidAsk_price);
        Orders.add(ordered);
        id++;
    }
    Order findOrder_with_Id(int id){
        Iterator<Order> it = Orders.iterator();
        while(it.hasNext()){
            Order hold = it.next();
            if (hold.id == id){
                return hold;
            }
        }
        // fail return
        return null;
    }
    void orderList(){
        System.out.println(Orders);
        Vector<Order> tmp = new Vector<>();
        int Osize = Orders.size();
        for(int j = 0; j < Osize; j++) {
            double max = 0;
            Order hold;
            Order highest = Orders.get(0);
            for(int i = 0; i <  Orders.size(); i++) {
                hold = Orders.get(i);
                if (hold.bidAsk_price > max){
                    max = hold.bidAsk_price;
                    highest = hold;
                }
            }
            tmp.add(highest);
            Orders.remove(highest);
        }
        Orders = tmp;
        System.out.println(Orders);
    }
    void tryFillBuy(Order buyOrder){     
        Order hold;
        Iterator<Order> it = Orders.iterator();
        while(it.hasNext()){
            hold = it.next();
            if ((hold.buySell == true) && (hold.crypto == buyOrder.crypto)){

            }
        }
    }
    void matchEngine(){
        orderList(); 
        Order hold;
        for(int i = 0; i <  Orders.size(); i++) {
            hold = Orders.get(i);
            //buy
            if(hold.buySell == false){
                tryFillBuy(hold);
            }
            //sell
            else{

            }
        }
    }
    void CancelOrder(int id){
        if (findOrder_with_Id(id) == null){
            return;
        }
        else{
            Order find = findOrder_with_Id(id);
            if(find.Filled > 0){
                return;
            }
            else{
                Orders.remove(find);
            }
        }
    }
}
