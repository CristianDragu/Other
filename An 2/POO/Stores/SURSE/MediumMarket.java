import java.util.Vector;

public class MediumMarket extends Magazin {

    public MediumMarket(){
        this.tip="MediumMarket";
    }
    
    @Override
    public double calculScutiriTaxe() {
        
        double res=0,sum,sumcategorie;
        boolean sem;
        Vector<String> vizitari = new Vector();
        
        sum=this.getTotalCuTaxe();
        for(int i=0;i<facturi.size();i++){
            for(int j=0;j<facturi.get(i).produsecomandate.size();j++){
                sem=false;
                if(vizitari.contains(facturi.get(i).produsecomandate.get(j).getProdus().getCategorie())){
                    sem=true;
                    break;
                }
                if(sem==false){
                    vizitari.addElement(facturi.get(i).produsecomandate.get(j).getProdus().getCategorie());
                }
            }
        }
        
        for(int i=0;i<vizitari.size();i++){
            sumcategorie=0;
            for(int j=0;j<facturi.size();j++)
                for(int k=0;k<facturi.get(j).produsecomandate.size();k++)
                    if(vizitari.get(i).compareTo(facturi.get(j).produsecomandate.get(k).getProdus().getCategorie()) == 0)
                        sumcategorie += facturi.get(j).produsecomandate.get(k).getProdus().getPret() * facturi.get(j).produsecomandate.get(k).getCantitate() * ((100+facturi.get(j).produsecomandate.get(k).getTaxa())/100);
            if(sumcategorie > sum/2){
                return sum / 20;
            }
        }
        
        return 0;
    }
    
    public double calculScutiriTaxeTara(String tara){
        double sum;
        
        sum = getTotalTaraCuTaxe(tara);
        if(calculScutiriTaxe()>0)
            return sum/20;
        return 0;
    }
    
}
