public class HyperMarket extends Magazin {

    public HyperMarket(){
        this.tip="HyperMarket";
    }
    
    @Override
    public double calculScutiriTaxe() {
        double res=0,sum;
        sum=this.getTotalCuTaxe();
        for(int i=0;i<facturi.size();i++)
            if(facturi.get(i).getTotalCuTaxe() > sum/10){
                return this.getTotalCuTaxe() / 100;
            }
        return 0;
    }
    
    public double calculScutiriTaxeTara(String tara){
        double sum;
        
        sum = getTotalTaraCuTaxe(tara);
        if(calculScutiriTaxe()>0)
            return sum/100;
        return 0;
    }
    
}
