public class ProdusComandat {
    
    private Produs produs;
    private double taxa;
    private double cantitate;
    
    public void setProdus(Produs produs){
        this.produs=produs;
    }    
    
    public Produs getProdus(){
        return this.produs;
    }
    
    public void setTaxa(double taxa){
        this.taxa=taxa;
    }
    
    public double getTaxa(){
        return this.taxa;
    }
    
    public void setCantitate(double cantitate){
        this.cantitate=cantitate;
    }
    
    public double getCantitate(){
        return this.cantitate;
    }
    
    public String toString(){
        return this.produs.toString() +"..."+ taxa +"% * "+ cantitate;
    }
}
