import java.util.Vector;

public class Produs {
    
    private String denumire, categorie, taraOrigine;
    private double pret;
    
    public void setDenumire(String denumire){
        this.denumire=denumire;
    }
    
    public String getDenumire(){
        return this.denumire;
    }
    
    public void setCategorie(String categorie){
        this.categorie=categorie;
    }
    
    public String getCategorie(){
        return this.categorie;
    }
    
    public void setTaraOrigine(String taraOrigine){
        this.taraOrigine=taraOrigine;
    }
    
    public String getTaraOrigine(){
        return this.taraOrigine;
    }
    
    public void setPret(double pret){
        this.pret=pret;
    }
    
    public double getPret(){
        return this.pret;
    }
    
    public String toString(){
        return this.getDenumire() +" "+ this.getCategorie() +" "+ this.getTaraOrigine() +" "+ this.getPret();
    }
}
