import java.util.Vector;

public abstract class Magazin implements IMagazin{
    
    public String nume;
    public Vector<Factura> facturi = new Vector<Factura>();
    public String tip;
    
    public double getTotalFaraTaxe(){      
        double sum=0;
        for(int i=0;i<facturi.size();i++)
            sum += facturi.get(i).getTotalFaraTaxe();
        return sum;        
    }
    
    public double getTotalCuTaxe(){      
        double sum=0;
        for(int i=0;i<facturi.size();i++)
            sum += facturi.get(i).getTotalCuTaxe();
        return sum;
    }
    
    public double getTotalCuTaxeScutite(){
        return this.getTotalCuTaxe() - calculScutiriTaxe();
    }
    
    public double getTotalTaraFaraTaxe(String tara){
        double sum=0;
        for(int i=0;i<facturi.size();i++)
            sum += facturi.get(i).getTotalTaraFaraTaxe(tara);
        return sum;        
    }
    
    public double getTotalTaraCuTaxe(String tara){
        double sum=0;
        for(int i=0;i<facturi.size();i++)
            sum += facturi.get(i).getTotalTaraCuTaxe(tara);
        return sum;        
    }
    
    public double getTotalTaraCuTaxeScutite(String tara){
        return this.getTotalTaraCuTaxe(tara) - calculScutiriTaxeTara(tara);
    }
    
    public String toString(){
        String output = "";
        
        output += nume + " : " + tip + "\r\n";
        output += super.toString();
        
        return output;
    }
}
