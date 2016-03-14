public class MagazinFactory {
    
    public static Magazin createMagazin(String magazinType){
        if("MiniMarket".equalsIgnoreCase(magazinType))
            return new MiniMarket();
        else if("MediumMarket".equalsIgnoreCase(magazinType))
            return new MediumMarket();
        else if("HyperMarket".equalsIgnoreCase(magazinType))
            return new HyperMarket();
        return null;
    }
    
}
