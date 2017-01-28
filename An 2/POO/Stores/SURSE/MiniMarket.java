import java.util.HashMap;
import java.util.Vector;

public class MiniMarket extends Magazin {

    public MiniMarket(){
        this.tip="MiniMarket";
    }
    @Override
    public double calculScutiriTaxe() {
        
        double res=0,sum,sumtara;
        
        sum=this.getTotalCuTaxe();
        for(String tara: Gestiune.tari){
            sumtara=this.getTotalTaraCuTaxe(tara);
            if(sumtara>(sum/2))
                return sum/10;
        }
        
        return 0;
    }
    
    public double calculScutiriTaxeTara(String tara){
        
        double sum;
        
        sum = getTotalTaraCuTaxe(tara);
        if(calculScutiriTaxe()>0)
            return sum/10;
        return 0;
    }
    
}
