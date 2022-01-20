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
    
    // Order constructer if order is a market order
    public Order(int id, boolean buySell,int Quantity, Crypto crypto){
        this.id = id;
        this.buySell = buySell;
        this.marketLimit = false;
        this.Quantity = Quantity;
        this.Filled = 0;
        this.crypto = crypto;
        // the prices is taken as the current market price of the crypto
        this.bidAsk_price = crypto.avgprice;
    }
    // Order constructer if order is a limit order
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

// OrderBook class Manages all of the Orders
public class OrderBook{
    // Vector of Orders holds all the current orders in circulation
    private static Vector<Order> Orders = new Vector<>();
    private int id = 0;
    // function adds a market order
    int addOrder(Trader trader,boolean buySell,int Quantity, Crypto crypto)    
    {
        //checks if the trader is approved
        if (trader.approved==false){
            System.out.println("Trader not Approved");
            return -1;
        }
        // calls the Order constructer for market
        Order ordered = new Order(id,buySell,Quantity,crypto);
        // adds the order to the global Orders Vector
        Orders.add(ordered);
        // the order is added to the traders transactions vector
        trader.Transactions.add(id);
        // the id is incremented
        id++;       
        return (id - 1);
    }
    // function adds a limit order
    int addOrder(Trader trader,boolean buySell,int Quantity, Crypto crypto, double bidAsk_price)    
    {
        //checks if the trader is approved
        if (trader.approved==false){
            System.out.println("Trader not Approved");
            return -1;
        }
        Order ordered = new Order(id,buySell,Quantity,crypto,bidAsk_price);
        // adds the order to the global Orders Vector
        Orders.add(ordered);
        // the order is added to the traders transactions vector
        trader.Transactions.add(id);
        // the id is incremented
        id++;
        return (id - 1);
    }

    // function returns the Order with the parsed id
    Order findOrder_with_Id(int id){
        // the global orders vecter is Iterated through
        Iterator<Order> it = Orders.iterator();
        while(it.hasNext()){
            Order hold = it.next();
            // check if the current Orders id matches the one we are searching for
            if (hold.id == id){
                // if it is then it is returned
                return hold;
            }
        }
        // If order isn't found then null is returned
        return null;
    }
    // The Orderbook is looped through printing all the orders' Quantities
    // this function is used for internal testing
    void printOrders(){
        Iterator<Order> it = Orders.iterator();
        while(it.hasNext()){
        Order hold = it.next();
           System.out.println(hold.Quantity);
        }
    }
    // all of a Traders' orders are outputted
    public void ViewTradersOrders(Trader trader){
        // checks if the Trader has been approved
        if (trader.approved==false){
            System.out.println("Trader not Approved");
            return;
        }
        // Iterates through allof the Traders' orders printing them out
        System.out.println("Orders by Trader: " + trader.username);
        System.out.println("ID\tCrypto\tQuantity\tFilled\tPrice\tType");
        for(int j = 0; j < trader.Transactions.size(); j++) {
            Order temp = findOrder_with_Id(trader.Transactions.get(j));
            if (temp!=null){
                System.out.print(temp.id+"\t"+temp.crypto.symbol+"\t"+temp.Quantity+"\t\t"+temp.Filled+"\t"+temp.bidAsk_price +"\t");
                if (temp.buySell == true){
                    System.out.println("SELL");
                }
                else{
                    System.out.println("BUY");
                }
            }
        }
    }

    // Orders the list from highest price to lowest price
    void orderList(){
        // tmp will hold the Ordered vector
        Vector<Order> tmp = new Vector<>();
        int Osize = Orders.size();
        // the Order vector is iterated through
        for(int j = 0; j < Osize; j++) {
            double max = 0;
            Order hold;
            Order highest = Orders.get(0);
            // loops through the orders getting the largest Order each time
            for(int i = 0; i <  Orders.size(); i++) {
                hold = Orders.get(i);
                if (hold.bidAsk_price > max){
                    max = hold.bidAsk_price;
                    highest = hold;
                }
            }
            // the largest Order is added to the tmp vector and removed temporarily
            // form the global Vector (Orders)
            tmp.add(highest);
            Orders.remove(highest);
        }
        // the Orders vector is set to the now Ordered list
        Orders = tmp;
    }

    // function attempts to fill the sell order
    void tryFillBuy(Order buyOrder){    
        // the Orders are iterated through
        Iterator<Order> it = Orders.iterator();
        while(it.hasNext()){
            Order hold = it.next();
            // checks if the current order is a sell order if the crypto type matches and if the price is less or equal to the buy order
            if ((hold.buySell == true) && (hold.crypto == buyOrder.crypto) && (hold.bidAsk_price <= buyOrder.bidAsk_price)){
                // checks if the buy order is larger or smaller than the sell or if they're equal 
                // if the buy Order is smaller then it is cancelled out
                if ((hold.Quantity - hold.Filled) > (buyOrder.Quantity - buyOrder.Filled)){             
                    int rhs = buyOrder.Quantity - buyOrder.Filled;
                    // the sell order is filled out as much as it can be
                    hold.Filled += rhs;
                    Orders.remove(buyOrder);
                    // if the buy order is removed we are done here and the funciton returns
                    return;
                }
                // if they're equal then both orders cancel out
                else if ((hold.Quantity - hold.Filled) == (buyOrder.Quantity - buyOrder.Filled)){
                    Orders.remove(hold);
                    Orders.remove(buyOrder);
                    // if the buy order is removed we are done here and the funciton returns
                    return;
                }
                // if the buy Order is larger then the sell order is cancelled out
                else{
                    int lhs = hold.Quantity - hold.Filled;
                    // the buy order is filled as much as it can
                    buyOrder.Filled += lhs;
                    Orders.remove(hold);
                }
            }
        }
    }
    // function tries to fill the sell order
    // similar in implementation to above function
    void tryFillSell(Order sellOrder){   
        Iterator<Order> it = Orders.iterator();
        while(it.hasNext()){
            Order hold = it.next();
            if ((hold.buySell == false) && (hold.crypto == sellOrder.crypto) && (hold.bidAsk_price >= sellOrder.bidAsk_price)){
                if ((hold.Quantity - hold.Filled) > (sellOrder.Quantity - sellOrder.Filled)){             
                    int rhs = sellOrder.Quantity - sellOrder.Filled;
                    hold.Filled += rhs;
                    Orders.remove(sellOrder);
                    return;
                }
                else if ((hold.Quantity - hold.Filled) == (sellOrder.Quantity - sellOrder.Filled)){
                    Orders.remove(hold);
                    Orders.remove(sellOrder);
                    return;
                }
                else{
                    int lhs = hold.Quantity - hold.Filled;
                    sellOrder.Filled += lhs;
                    Orders.remove(hold);
                }
            }
        }
    }

    // function tries to match buy orders with sell orders
    void matchEngine(){
        System.out.println(Orders);
        // the list is first ordered in descending order by price
        orderList(); 
        System.out.println(Orders);
        Order hold;
        for(int i = 0; i <  Orders.size(); i++) {
            hold = Orders.get(i);
            //buy
            if(hold.buySell == false){
                //function is called to match the buy order
                tryFillBuy(hold);
            }
            //sell
            else{
                //function is called to match the sell order
                tryFillSell(hold);
            }
        }
        System.out.println(Orders);
    }

    // function allows a trader to cancel their order as long as the order hasn't been filled at all
    void CancelOrder(Trader trader,int id){
        if (trader.approved==false){
            System.out.println("Trader not Approved");
            return;
        }
        // if the order cannot be found it returns
        if (findOrder_with_Id(id) == null){
            return;
        }
        else{
            Order find = findOrder_with_Id(id);
            // if the order has already been partially filled it doesn't remove it
            if(find.Filled > 0){
                return;
            }
            // order is removed
            else{
                Orders.remove(find);
                trader.Transactions.remove(id);
            }
        }
    }
}
