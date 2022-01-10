import java.util.Vector;
class Order {
    // false for buy
    boolean buySell;
    // false for market
    boolean marketLimit;
    int Quantity;
    double bidAsk_price;
    public Order(boolean buySell,int Quantity,double bidAsk_price){
        this.buySell = buySell;
        this.marketLimit = false;
        this.Quantity = Quantity;
        this.bidAsk_price = bidAsk_price;
    }
    public Order(boolean buySell,boolean marketLimit,int Quantity,double bidAsk_price){
        this.buySell = buySell;
        this.marketLimit = marketLimit;
        this.Quantity = Quantity;
        this.bidAsk_price = bidAsk_price;
    }
}

public class OrderBook{
    private Vector<Order> Orders = new Vector<>();
}
