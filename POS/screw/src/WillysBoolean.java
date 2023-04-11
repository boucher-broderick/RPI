import java.util.*;

class WillysBoolean {
  private boolean value;
  private WillysBoolean(boolean value) {
    this.value = value;
  }
  private static Map<WillysBoolean, WillysBoolean> cache = 
                                   new HashMap<WillysBoolean, WillysBoolean>();
  public static WillysBoolean valueOf(boolean value) {
    WillysBoolean tmp = new WillysBoolean(value);
    if (cache.containsKey(tmp))
      return cache.get(tmp);
    else {
      cache.put(tmp,tmp);
      return tmp;
    }
  }
  
  
  public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      System.out.println("Enter boolean value");
      boolean value=sc.nextBoolean();
      WillysBoolean v=valueOf(value);
      System.out.println(v.value);
  }
}
