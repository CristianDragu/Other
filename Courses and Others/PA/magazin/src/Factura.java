import java.text.DecimalFormat;
import java.util.Vector;

public class Factura {
    public String denumire;
    public Vector<ProdusComandat> produsecomandate = new Vector<ProdusComandat>();
    
    public double getTotalFaraTaxe(){      
        double sum=0;
        for(int i=0;i<produsecomandate.size();i++)
            sum += produsecomandate.get(i).getProdus().getPret() * produsecomandate.get(i).getCantitate();
        return sum;        
    }
    
    public double getTotalCuTaxe(){
        double sum=0;
        for(int i=0;i<produsecomandate.size();i++)
            sum += produsecomandate.get(i).getProdus().getPret() * produsecomandate.get(i).getCantitate() * ((produsecomandate.get(i).getTaxa() + 100)/100);
        return sum;
    }
    
    public double getTaxe(){
        double sum=0;
        for(int i=0;i<produsecomandate.size();i++)
            sum += produsecomandate.get(i).getProdus().getPret() * (produsecomandate.get(i).getTaxa()/100);
        return sum;
    }
    
    public double getTotalTaraFaraTaxe(String tara){
        double sum=0;
        for(int i=0;i<produsecomandate.size();i++)
            if(produsecomandate.get(i).getProdus().getTaraOrigine().compareTo(tara) == 0)
                sum += produsecomandate.get(i).getProdus().getPret() * produsecomandate.get(i).getCantitate();
        return sum;        
    }
    
    public double getTotalTaraCuTaxe(String tara){
        double sum=0;
        for(int i=0;i<produsecomandate.size();i++)
            if(produsecomandate.get(i).getProdus().getTaraOrigine().compareTo(tara) == 0)
                sum += produsecomandate.get(i).getProdus().getPret() * produsecomandate.get(i).getCantitate() * ((produsecomandate.get(i).getTaxa() + 100)/100);
        return sum;
    }
    
    public double getTaxeTara(String tara){
        double sum=0;
        for(int i=0;i<produsecomandate.size();i++)
            if(produsecomandate.get(i).getProdus().getTaraOrigine().compareTo(tara) == 0)
                sum += produsecomandate.get(i).getProdus().getPret() * (produsecomandate.get(i).getTaxa()/100);
        return sum;        
    }
    
    public String toString(){
        DecimalFormat numberFormat = new DecimalFormat("#.####");
        String output = "";
        
        output = denumire + "\r\n\r\n" + "Total " + numberFormat.format(getTotalFaraTaxe()) + " " + numberFormat.format(getTotalCuTaxe()) + "\r\n\r\n" + "Tara" + "\r\n";
        for(String tara: Gestiune.tari){
            if(getTotalTaraFaraTaxe(tara) == 0)
                output = output + tara + " 0"+ "\r\n";
            else
                output = output + tara + " " + numberFormat.format(getTotalTaraFaraTaxe(tara)) + " " + numberFormat.format(getTotalTaraCuTaxe(tara)) + "\r\n";
        }
        return output;
    }
}
