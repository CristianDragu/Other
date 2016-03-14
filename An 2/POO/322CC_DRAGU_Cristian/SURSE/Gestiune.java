import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.Vector;

public class Gestiune {
    
    private static Gestiune instance = null;
    private Gestiune(){}
    public static Gestiune getInstance(){
        if (instance == null)
            instance = new Gestiune();
        return instance;
    }
    
    public static Vector<String> tari;
    public static Vector<Produs> produse;
    public static HashMap<String,HashMap<String,Double>> taxe;
    public static Vector<Magazin> magazine;
    
    public static void ProduseRead(File produsetxt) throws FileNotFoundException, IOException{
        BufferedReader buffer = new BufferedReader(new FileReader(produsetxt));
        String line;
        
        produse = new Vector<Produs>();
        tari = new Vector<String>();
        
        line = buffer.readLine();
        if(line != null){
            StringTokenizer token = new StringTokenizer(line," ");
            if(token.hasMoreTokens()){
                token.nextToken();
                token.nextToken();
                while(token.hasMoreTokens()){
                    tari.addElement(token.nextToken().toString());
                }
            }
        }
        
        while((line=buffer.readLine()) != null){
            StringTokenizer token = new StringTokenizer(line," ");
            {// citire produse
                String denumire = token.nextToken().toString();
                String categorie = token.nextToken().toString();
                for(String tara: Gestiune.tari){
                    Produs produs = new Produs();
                    produs.setDenumire(denumire);
                    produs.setCategorie(categorie);
                    produs.setTaraOrigine(tara);
                    try{
                        produs.setPret(Double.parseDouble(token.nextToken()));
                    }catch(NoSuchElementException e){
                        
                    }
                    produse.add(produs);
                }
            }
        }
        
    }
    
    public static void TaxeRead(File taxetxt) throws FileNotFoundException, IOException{
        BufferedReader buffer = new BufferedReader(new FileReader(taxetxt));
        String line;
        
        taxe = new HashMap<String,HashMap<String,Double>>();
        
        line = buffer.readLine();
        while((line=buffer.readLine()) != null){
            int i=0;
            StringTokenizer token = new StringTokenizer(line," ");
            if(token.hasMoreTokens()){
                String categorie = new String(token.nextToken().toString());
                while(token.hasMoreTokens()){
                    HashMap<String,Double> aux = new HashMap<String,Double>();
                    if(taxe.get(tari.elementAt(i))!=null)
                        aux = taxe.get(tari.elementAt(i));
                    aux.put(categorie, Double.parseDouble(token.nextToken()));
                    taxe.put(tari.elementAt(i), aux);
                    i++;
                }
            }
        }
    }
    
    public static void FacturiRead(File facturitxt) throws FileNotFoundException, IOException{
        BufferedReader buffer = new BufferedReader(new FileReader(facturitxt));
        String line;
        
        magazine = new Vector<Magazin>();
        
        while((line=buffer.readLine())!=null){
            if(!(line.equals(""))){
                if(line.contains("Magazin:")){
                    StringTokenizer token = new StringTokenizer(line,":");
                    token.nextToken();
                    magazine.addElement(MagazinFactory.createMagazin(token.nextToken().toString()));
                    magazine.lastElement().nume = token.nextToken().toString();
                }
                else{
                    Factura factura = new Factura();
                    factura.denumire = line;
                    line=buffer.readLine();
                    while(!("".equals(line=buffer.readLine())) && line!=null){
                        if("".equals(line)) System.out.println("astalavista");
                        StringTokenizer token = new StringTokenizer(line," ");
                        Produs produs = new Produs();
                        produs.setDenumire(token.nextToken().toString());
                        produs.setTaraOrigine(token.nextToken().toString());
                        for(Produs eachprodus: Gestiune.produse){
                            if(eachprodus.getDenumire().equals(produs.getDenumire()) && eachprodus.getTaraOrigine().equals(produs.getTaraOrigine())){
                                produs.setCategorie(eachprodus.getCategorie());
                                produs.setPret(eachprodus.getPret());
                                break;
                            }
                        }
                        ProdusComandat produscomandat = new ProdusComandat();
                        produscomandat.setProdus(produs);
                        produscomandat.setTaxa(taxe.get(produs.getTaraOrigine()).get(produs.getCategorie()));
                        produscomandat.setCantitate(Double.parseDouble(token.nextToken()));
                        factura.produsecomandate.addElement(produscomandat);
                    }
                    magazine.lastElement().facturi.addElement(factura);
                }
            }
        }
        Collections.sort(magazine,new Comparator<Magazin>(){
            public int compare(Magazin m1, Magazin m2){
                if(m1.tip.compareTo(m2.tip) == 0)
                    if(m1.getTotalFaraTaxe()-m2.getTotalFaraTaxe() < 0)
                        return -1;
                    else
                        return 1;
                else
                    return (-1)*m1.tip.compareTo(m2.tip);
            }
        });
    }
    
    public static void PrintOut() throws IOException{
        BufferedWriter out= new BufferedWriter(new FileWriter("out.txt"));
        DecimalFormat numberFormat = new DecimalFormat("#.####");
        
        Collections.sort(tari);
        
        String type;
        type = magazine.firstElement().tip;
        out.write(type);
        
        for(Magazin magazin: magazine){
            if(magazin.tip != type){
                out.newLine();
                out.write(magazin.tip);
                type = magazin.tip;
            }
            out.newLine();
            out.write(magazin.nume);
            out.newLine();
            out.newLine();
            out.write("Total " + numberFormat.format(magazin.getTotalFaraTaxe()) + " " + numberFormat.format(magazin.getTotalCuTaxe()) + " " + numberFormat.format(magazin.getTotalCuTaxeScutite()));
            out.newLine();
            out.newLine();
            out.write("Tara");
            for(String tara: tari){
                out.newLine();
                if(magazin.getTotalTaraFaraTaxe(tara) == 0)
                    out.write(tara + " 0");
                else
                    out.write(tara + " " + numberFormat.format(magazin.getTotalTaraFaraTaxe(tara)) + " " + numberFormat.format(magazin.getTotalTaraCuTaxe(tara)) + " " + numberFormat.format(magazin.getTotalTaraCuTaxeScutite(tara)));
            }
            out.newLine();
            for(Factura factura:magazin.facturi){
                out.newLine();
                out.write(factura.toString());
            }
        }
        
        out.flush();
        out.close();
    }
}