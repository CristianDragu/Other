import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.table.DefaultTableModel;

public class Interfata {
    
    public static JFrame index, fisiere, statistica, administrare, printframe, deleteframe, logframe;
    public static JButton b1, b2, b3;
    public static JButton signup, login, file1, file2, file3;
    public static JButton save, cancel;
    public static JTable printTable;
    public static JTextField produs , categorie, tara, user, password, user2, produsetxt, taxetxt, facturitxt;
    public static JFileChooser fc = new JFileChooser();
    public static Gestiune gestiune = null;
    public static File produseFile = null, taxeFile = null, facturiFile = null;
    
    static class openListener implements ActionListener
    {
        String filename;
        public openListener(String filename)
        {
            this.filename = filename;
        }
        @Override
        public void actionPerformed(ActionEvent e) {
            Interfata.fc.setFileFilter(new FileNameExtensionFilter("Text Files", "txt"));
            int returnval = Interfata.fc.showOpenDialog(Interfata.fisiere);
            File file = null;
            if (returnval == JFileChooser.APPROVE_OPTION)
            {
                file = Interfata.fc.getSelectedFile();
            }
            if (file != null)
            {
                switch (filename)
                {
                    case "produse":
                        Interfata.produseFile = file;
                        produsetxt.setText(Interfata.fc.getSelectedFile().getAbsolutePath());
                        break;
                    case "taxe":
                        Interfata.taxeFile = file;
                        taxetxt.setText(Interfata.fc.getSelectedFile().getAbsolutePath());
                        break;
                    case "facturi":
                        Interfata.facturiFile = file;
                        facturitxt.setText(Interfata.fc.getSelectedFile().getAbsolutePath());
                        break;
                }
            }
        }
        
    }
    
    public static void run(){
        gestiune = Gestiune.getInstance();
        try{
            gestiune.ProduseRead(produseFile);
            gestiune.TaxeRead(taxeFile);
            gestiune.FacturiRead(facturiFile);
            gestiune.PrintOut();
        }
        catch(FileNotFoundException exc){

        }
        catch(IOException exc){

        }

        String[] names = {"Produs", "Categorie", "Tara", "Pret"};
        Object[][] data = new Object[gestiune.produse.size()][4];
        for(int i=0;i<gestiune.produse.size();i++){
            data[i][0]=gestiune.produse.elementAt(i).getDenumire();
            data[i][1]=gestiune.produse.elementAt(i).getCategorie();
            data[i][2]=gestiune.produse.elementAt(i).getTaraOrigine();
            data[i][3]=gestiune.produse.elementAt(i).getPret();
        }

        printTable = new JTable(new DefaultTableModel(data, names));
        printTable.setAutoCreateRowSorter(true);
        printTable.setRowHeight(20);
    }
    
    static class actionchoice implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            if(e.getSource() == save){
                run();
                index.setVisible(true);
                fisiere.dispatchEvent(new WindowEvent(fisiere, WindowEvent.WINDOW_CLOSING));
            }
            else
                if(e.getSource() == cancel){
                    index.setVisible(true);
                    fisiere.dispatchEvent(new WindowEvent(fisiere, WindowEvent.WINDOW_CLOSING));
                }
        }
        
    }
    
    static class action implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            if(e.getSource() == b1){
                index.setVisible(false);
                filesWindow();
            }
            else
                if(e.getSource() == b3){
                    index.setVisible(false);
                    statisticWindow();
                }
                else
                    if(e.getSource() == b2){
                        index.setVisible(false);
                        administrationWindow();
                    }
        }
        
    }
    
    public static void initWindow(JFrame f){
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        f.setSize(dim.width/3,dim.height/3);
        f.setLocation(dim.width/2 - f.getSize().width/2, dim.height/2 - f.getSize().height/2);
        f.setVisible(true);
    }
    
    public static JTextField initTextField(JTextField tf){
        tf = new JTextField("", 20);
        
        tf.setEditable(true);
        tf.setBorder(new EtchedBorder());
        tf.setBackground(Color.white);
        tf.setPreferredSize(new Dimension(20,30));
        
        return tf;
    }
    
    public static void filesWindow(){
        fisiere = new JFrame("Incarcare fisiere");
        initWindow(fisiere);
        
        fisiere.addWindowListener(
        new WindowAdapter() {
            @Override
            public void windowClosing(final WindowEvent e) {
                index.setVisible(true);
                fisiere.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            }
        });
        
        fisiere.setLayout(new GridLayout(3,1));
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        fisiere.setPreferredSize(new Dimension(dim.width/3,dim.height/2));
        fisiere.setLocation(dim.width/2 - fisiere.getSize().width/2, dim.height/2 - fisiere.getSize().height/2);
        
        JLabel messagelabel = new JLabel("Deschideti fisierele!",JLabel.CENTER);
        fisiere.getContentPane().add(messagelabel);

        JPanel filep1 = new JPanel();
        filep1.setLayout(new GridLayout(3,3,0,10));
        filep1.setBorder(new EmptyBorder(0,20,0,20));
        
        JLabel filel1 = new JLabel("Produse ");
        JLabel filel2 = new JLabel("Taxe");
        JLabel filel3 = new JLabel("Facturi");

        file1 = new JButton(new ImageIcon("folder.png"));
        file1.addActionListener(new openListener("produse"));
        file2 = new JButton(new ImageIcon("folder.png"));
        file2.addActionListener(new openListener("taxe"));
        file3 = new JButton(new ImageIcon("folder.png"));
        file3.addActionListener(new openListener("facturi"));
        
        JPanel p1 = new JPanel();
        JPanel p2 = new JPanel();
        JPanel p3 = new JPanel();
        p1.add(file1);
        p2.add(file2);
        p3.add(file3);
        filep1.add(filel1);
        filep1.add((produsetxt = initTextField(produsetxt)));
        filep1.add(p1);
        filep1.add(filel2);
        filep1.add((taxetxt = initTextField(taxetxt)));
        filep1.add(p2);
        filep1.add(filel3);
        filep1.add((facturitxt = initTextField(facturitxt)));
        filep1.add(p3);
        
        fisiere.getContentPane().add(filep1);
        
        JPanel panelbuttons = new JPanel();
        JPanel panelsave = new JPanel();
        JPanel panelcancel = new JPanel();
        save = new JButton("Save", new ImageIcon("save.png"));
        cancel = new JButton("Cancel", new ImageIcon("cancel.png"));
        panelsave.add(save);
        save.addActionListener(new actionchoice());
        panelcancel.add(cancel);
        cancel.addActionListener(new actionchoice());
        panelbuttons.add(panelsave);
        panelbuttons.add(panelcancel);
        panelbuttons.setBorder(new EmptyBorder(20,0,0,0));
        panelbuttons.setLayout(new GridLayout(1,2));
        fisiere.getContentPane().add(panelbuttons);
        
        fisiere.validate();
        fisiere.pack();
    }
    
    public static void statisticWindow(){
        statistica = new JFrame("Statistica");
        initWindow(statistica);
        statistica.setLayout(new GridLayout(8,1));
        
        statistica.addWindowListener(
        new WindowAdapter() {
            @Override
            public void windowClosing(final WindowEvent e) {
                index.setVisible(true);
                statistica.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            }
        });
        
        if(gestiune!=null){
            DecimalFormat numberFormat = new DecimalFormat("#.####");
            
            double max = gestiune.magazine.firstElement().getTotalCuTaxe();
            Magazin market = gestiune.magazine.firstElement();
            for(Magazin magazin: gestiune.magazine){
                if(magazin.getTotalCuTaxe() > max){
                    max = magazin.getTotalCuTaxe();
                    market = magazin;
                }
            }
            
            String[] names = {"Denumire", "Total fara taxe", "Total cu taxe", "Total cu taxe scutite"};
            Object[][] data = { {market.nume, numberFormat.format(market.getTotalFaraTaxe()), numberFormat.format(market.getTotalCuTaxe()), numberFormat.format(market.getTotalCuTaxeScutite())}};
            
            JTable tableView1 = new JTable(data, names);
            tableView1.setRowHeight(30);
            JScrollPane scrollpane = new JScrollPane(tableView1);
            tableView1.setEnabled(false);
            scrollpane.setVisible(true);
            scrollpane.setPreferredSize(new Dimension(statistica.getSize().width,52));
            JLabel label1 = new JLabel("Magazinul cu cele mai mari vanzari (total cu taxe):",SwingConstants.CENTER);
            statistica.add(label1);
            statistica.add(scrollpane);
            
            
            
            DefaultTableModel model = new DefaultTableModel();
            model.addColumn("Tara");
            model.addColumn("Denumire");
            model.addColumn("Total fara taxe");
            model.addColumn("Total cu taxe");
            model.addColumn("Total cu taxe scutite");
            JTable tableView2 = new JTable(model);
            for(String tara:gestiune.tari){
                max = gestiune.magazine.firstElement().getTotalTaraCuTaxe(tara);
                market = gestiune.magazine.firstElement();
                for(Magazin magazin: gestiune.magazine){
                    if(magazin.getTotalTaraCuTaxe(tara)> max){
                        max = magazin.getTotalTaraCuTaxe(tara);
                        market = magazin;
                    }
                }
                Object[] datatari = { tara, market.nume, numberFormat.format(market.getTotalFaraTaxe()), numberFormat.format(market.getTotalCuTaxe()), numberFormat.format(market.getTotalCuTaxeScutite())};
                model = (DefaultTableModel) tableView2.getModel();
                model.addRow(datatari);
                tableView2 = new JTable(model);
            }
            tableView2.setRowHeight(30);
            JScrollPane scrollpane2 = new JScrollPane(tableView2);
            tableView2.setEnabled(false);
            scrollpane2.setVisible(true);
            scrollpane2.setViewportView(tableView2);
            scrollpane2.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
            scrollpane2.setPreferredSize(new Dimension(statistica.getSize().width,gestiune.tari.size()*30+22));
            JLabel label2 = new JLabel("Magazinul cu cele mai mari vanzari pentru fiecare tara:",SwingConstants.CENTER);
            statistica.add(label2);
            statistica.add(scrollpane2);
            
            
            
            DefaultTableModel model2 = new DefaultTableModel();
            model2.addColumn("Categorie");
            model2.addColumn("Denumire");
            model2.addColumn("Total fara taxe");
            model2.addColumn("Total cu taxe");
            model2.addColumn("Total cu taxe scutite");
            JTable tableView3 = new JTable(model2);
            
            Vector<String> categorii = new Vector<String>();
            for (String tara: gestiune.taxe.keySet()){
                String key = tara;
                for (String categorie: gestiune.taxe.get(tara).keySet()){
                    categorii.add(categorie);
                }
                break;
            }
            
            for(String categorie: categorii){
                double summax=0;
                for(Magazin magazin: gestiune.magazine){
                    double sumcategorie=0;
                    for(Factura factura: magazin.facturi){
                        for(ProdusComandat produsComandat: factura.produsecomandate){
                            if(produsComandat.getProdus().getCategorie().compareTo(categorie) == 0){
                                sumcategorie += produsComandat.getProdus().getPret() * produsComandat.getCantitate() * ((100+produsComandat.getTaxa())/100);
                            }
                        }
                    }
                    if(sumcategorie > summax)
                        summax = sumcategorie;
                }
                Object[] datacategorie = { categorie, market.nume, numberFormat.format(market.getTotalFaraTaxe()), numberFormat.format(market.getTotalCuTaxe()), numberFormat.format(market.getTotalCuTaxeScutite())};
                model2 = (DefaultTableModel) tableView3.getModel();
                model2.addRow(datacategorie);
                tableView3 = new JTable(model2);
            }
            tableView3.setRowHeight(30);
            JScrollPane scrollpane3 = new JScrollPane(tableView3);
            tableView3.setEnabled(false);
            scrollpane3.setVisible(true);
            scrollpane3.setViewportView(tableView3);
            scrollpane3.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
            scrollpane3.setPreferredSize(new Dimension(200,categorii.size()*30+22));
            JLabel label3 = new JLabel("Magazinul cu cele mai mari vanzari pentru fiecare categorie:",SwingConstants.CENTER);
            statistica.add(label3);
            statistica.add(scrollpane3);
            
            
            
            double facturasummax = 0;
            Factura facturamax = new Factura();
            for(Magazin magazin: gestiune.magazine){
                for(Factura factura: magazin.facturi){
                    if(factura.getTotalFaraTaxe() > facturasummax){
                        facturasummax = factura.getTotalFaraTaxe();
                        market = magazin;
                        facturamax = factura;
                    }
                }
            }
            
            String[] names2 = {"Denumire factura", "Denumire magazin" ,"Total fara taxe", "Total cu taxe", "Total cu taxe scutite"};
            Object[][] datafactura = { {facturamax.denumire, market.nume, numberFormat.format(market.getTotalFaraTaxe()), numberFormat.format(market.getTotalCuTaxe()), numberFormat.format(market.getTotalCuTaxeScutite())}};
            
            JTable tableView4 = new JTable(datafactura, names2);
            tableView4.setRowHeight(30);
            JScrollPane scrollpane4 = new JScrollPane(tableView4);
            tableView4.setEnabled(false);
            scrollpane4.setVisible(true);
            scrollpane4.setPreferredSize(new Dimension(statistica.getSize().width,52));
            JLabel label4 = new JLabel("Magazinul cu cele mai mari vanzari (total cu taxe):",SwingConstants.CENTER);
            statistica.add(label4);
            statistica.add(scrollpane4);
            
            statistica.validate();
            statistica.pack();
        } 
    }
    
    public static void administrationWindow(){
        administrare = new JFrame("Administrare produse");
        administrare.setLayout(new GridLayout(1,1));
        initWindow(administrare);
        administrare.addWindowListener(
        new WindowAdapter() {
            @Override
            public void windowClosing(final WindowEvent e) {
                index.setVisible(true);
                administrare.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            }
        });
        
        JButton print = new JButton("Afisare produse");
        JButton add = new JButton("Adaugare produs");
        JButton delete = new JButton("Stergere produs");
        
        JPanel panel = new JPanel();
        JPanel panel1 = new JPanel();
        JPanel panel2 = new JPanel();
        JPanel panel3 = new JPanel();
        panel1.add(print);
        panel2.add(add);
        panel3.add(delete);
        panel.add(panel1);
        panel.add(panel2);
        panel.add(panel3);
        administrare.getContentPane().add(panel);
        
        print.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e){
                administrare.setVisible(false);
                printProduse();
            }
        });
        
        add.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent ae) {
                DefaultTableModel model = (DefaultTableModel) printTable.getModel();
                
                JPanel panel = new JPanel();
                JTextField nume = new JTextField();
                JTextField pret = new JTextField();
                nume = initTextField(nume);
                pret = initTextField(pret);
                
                String[] categorii = new String[gestiune.produse.size()/3];
                for(int i=0; i<gestiune.produse.size(); i+=3)
                    categorii[i/3] = gestiune.produse.get(i).getCategorie();
                    
                JComboBox categorie = new JComboBox(categorii);
                JComboBox tara = new JComboBox(gestiune.tari);
                panel.setLayout(new GridLayout(1,2));
                
                JLabel produsl = new JLabel("Nume");
                JLabel categoriel = new JLabel("Categorie");
                JLabel taral = new JLabel("Tara");
                JLabel pretl = new JLabel("Pret");
                
                JPanel labels = new JPanel();
                JPanel choices = new JPanel();
                labels.setLayout(new GridLayout(4,1));
                choices.setLayout(new GridLayout(4,1));
                labels.add(produsl);
                labels.add(categoriel);
                labels.add(taral);
                labels.add(pretl);
                choices.add(nume);
                choices.add(categorie);
                choices.add(tara);
                choices.add(pret);
                
                panel.add(labels);
                panel.add(choices);
                
                int result = JOptionPane.showConfirmDialog(administrare, panel, "Adaugare produs", JOptionPane.OK_CANCEL_OPTION);
                
                if(result == JOptionPane.OK_OPTION){
                    
                    String name = nume.getText();
                    String categ = String.valueOf(categorie.getSelectedItem());
                    String country = String.valueOf(tara.getSelectedItem());
                    String price = pret.getText();
                    
                    try {
                        BufferedReader buffer = new BufferedReader(new FileReader(produseFile));
                        BufferedWriter out= new BufferedWriter(new FileWriter("auxiliar.txt"));
                        
                        String line, lineout="";
                        boolean existaprod = false;
                        
                        line=buffer.readLine();
                        out.write(line);
                        out.newLine();
                        StringTokenizer token = new StringTokenizer(line," ");
                        token.nextToken();
                        token.nextToken();

                        Vector<String> tari = new Vector<String>();
                        while(token.hasMoreTokens()){
                            tari.add(token.nextToken().toString());
                        }
                        
                        while((line=buffer.readLine())!=null){
                            if(line.contains(name) && line.contains(categ)){
                                if(JOptionPane.showOptionDialog(null,"Doriti sa faceti modificari produsului " + name + " existent?", "Modifica", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == 0){
                                    lineout = "";
                                    lineout = name + " " + categ;
                                    token = new StringTokenizer(line," ");
                                    token.nextToken();
                                    token.nextToken();
                                    for(String t: tari){
                                        if(t.compareTo(country) == 0){
                                            lineout = lineout + " " + price;
                                            token.nextToken();
                                            existaprod = true;
                                        }
                                        else
                                            lineout = lineout + " " + token.nextToken().toString();
                                    }
                                }
                                else
                                    lineout = line;
                            }
                            else
                                lineout = line;
                            
                            out.write(lineout);
                            out.newLine();
                        }
                        
                        if(existaprod == false){
                            lineout = name + " " + categ;
                            
                            for(String t: tari){
                                if(t.compareTo(country) == 0){
                                    lineout = lineout + " " + price;
                                }
                                else
                                    lineout = lineout + " 0";
                            }
                            
                            out.write(lineout);
                            out.newLine();
                        }
                        
                        out.flush();
                        out.close();
                        
                        buffer = new BufferedReader(new FileReader("auxiliar.txt"));
                        out= new BufferedWriter(new FileWriter(produseFile));

                        while((line=buffer.readLine())!=null){
                            out.write(line);
                            out.newLine();
                        }

                        out.flush();
                        out.close();
                        
                    } catch (FileNotFoundException ex) {
                        Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    run();
                }
            }
        });
        
        delete.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                DefaultTableModel model = (DefaultTableModel) printTable.getModel();
                Vector data = model.getDataVector();
                
                if(data != null){
                    Object[] possibilities = new Object[data.size()];
                    for(int i=0; i<data.size(); i++)
                        possibilities[i]=data.get(i);

                    Vector result = (Vector) JOptionPane.showInputDialog(administrare,"Alegeti produs", "Stergere produs", JOptionPane.PLAIN_MESSAGE, UIManager.getIcon("OptionPane.questionIcon"),possibilities,possibilities[0]);

                    if(result != null)
                        for(int i=0; i<data.size(); i++){
                            if(result.equals(data.get(i))){
                                model.removeRow(i);
                                model.fireTableStructureChanged();
                                deleteProduse((String) result.get(0),(String) result.get(1), (String) result.get(2));
                            }
                        }
                }
            }
        });
        
        administrare.pack();
    }
    
    public static void printProduse(){
        printframe = new JFrame("Afisare produse");
        initWindow(printframe);
        printframe.addWindowListener(
        new WindowAdapter() {
            @Override
            public void windowClosing(final WindowEvent e) {
                administrare.setVisible(true);
                printframe.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            }
        });
 
        JScrollPane scrollpane = new JScrollPane(printTable);
        scrollpane.setPreferredSize(new Dimension(500, 300));
        printframe.add(scrollpane);
        printframe.pack();
    }
    
    public static void deleteProduse(String prod, String categ, String country){
        try {
            BufferedReader buffer = new BufferedReader(new FileReader(produseFile));
            BufferedWriter out= new BufferedWriter(new FileWriter("auxiliar.txt"));

            String line, lineout="";

            line=buffer.readLine();
            out.write(line);
            out.newLine();
            StringTokenizer token = new StringTokenizer(line," ");
            token.nextToken();
            token.nextToken();

            Vector<String> tari = new Vector<String>();
            while(token.hasMoreTokens()){
                tari.add(token.nextToken().toString());
            }
            while((line=buffer.readLine())!=null){
                if(line.contains(prod) && line.contains(categ)){
                    lineout = "";
                    lineout = prod + " " + categ;
                    token = new StringTokenizer(line," ");
                    token.nextToken();
                    token.nextToken();
                    for(String tara: tari){
                        if(tara.compareTo(country) == 0){
                            lineout = lineout + " 0";
                            token.nextToken();
                        }
                        else
                            lineout = lineout + " " + token.nextToken().toString();
                    }
                }
                else
                    lineout = line;

                out.write(lineout);
                out.newLine();
            }
            out.flush();
            out.close();

            buffer = new BufferedReader(new FileReader("auxiliar.txt"));
            out= new BufferedWriter(new FileWriter(produseFile));

            while((line=buffer.readLine())!=null){
                out.write(line);
                out.newLine();
            }

            out.flush();
            out.close();

        } catch (FileNotFoundException ex) {
            Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void logWindow(){
        logframe = new JFrame("User");
        initWindow(logframe);
        
        JTabbedPane tabbedpane= new JTabbedPane();
        JPanel tab1 = new JPanel();
        JPanel tab2 = new JPanel();
        
        tab1.setLayout(new GridLayout(2,1));
        JPanel filep1 = new JPanel();
        JPanel filep2 = new JPanel();
        
        JLabel filel1 = new JLabel("User");
        JLabel filel2 = new JLabel("Parola");
        filep1.setLayout(new GridLayout(2,1));
        filep1.add(filel1);
        filep1.add(filel2);
        
        user = initTextField(user);
        JPasswordField password = new JPasswordField(20);
        password.setBorder(new EtchedBorder());
        password.setBackground(Color.white);
        filep2.setLayout(new GridLayout(2,1));
        filep2.add(user);
        filep2.add(password);
        

        JPanel complete = new JPanel();
        complete.setLayout(new GridLayout(1,2));
        complete.add(filep1);
        complete.add(filep2);
        complete.setBorder(new EmptyBorder(0,10,20,10));
        tab1.add(complete);
        
        JPanel panelbuttons = new JPanel();
        JPanel panellog = new JPanel();
        login = new JButton("Login");
        panellog.add(login);
        login.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    BufferedReader logs = new BufferedReader(new FileReader("logs.txt"));
                    String line1,line2;
                    boolean sem = false;
                    while((line1=logs.readLine())!=null && (line2=logs.readLine())!=null){
                        String utilizator = user.getText();
                        String parola = password.getText();
                        if(utilizator.equals(line1) && parola.equals(line2)){
                            sem = true;
                            indexWindow();
                            logframe.setVisible(false);
                            break;
                        }
                    }
                    if(sem == false){
                        JOptionPane.showMessageDialog(logframe, "User sau parola gresita!", "Error", JOptionPane.ERROR_MESSAGE);
                        user.setText("");
                        password.setText("");
                    }
                } catch (FileNotFoundException ex) {
                    Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
                } catch (IOException ex) {
                    Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        
        panelbuttons.add(panellog);
        panelbuttons.setLayout(new GridLayout(1,1));
        tab1.setBorder(new EmptyBorder(20,10,0,10));
        tab1.add(panelbuttons);
        
        tabbedpane.addTab("Login", tab1);
        
        tab2.setLayout(new GridLayout(2,1));
        JPanel filep3 = new JPanel();
        JPanel filep4 = new JPanel();
        
        JLabel filel3 = new JLabel("User");
        JLabel filel4 = new JLabel("Parola");
        filep3.setLayout(new GridLayout(2,1));
        filep3.add(filel3);
        filep3.add(filel4);
        
        user2 = initTextField(user2);
        JPasswordField password2 = new JPasswordField(20);
        password2.setBorder(new EtchedBorder());
        password2.setBackground(Color.white);
        filep4.setLayout(new GridLayout(2,1));
        filep4.add(user2);
        filep4.add(password2);
        

        JPanel complete2 = new JPanel();
        complete2.setLayout(new GridLayout(1,2));
        complete2.add(filep3);
        complete2.add(filep4);
        complete2.setBorder(new EmptyBorder(0,10,20,10));
        tab2.add(complete2);
        
        JPanel panelbuttons2 = new JPanel();
        JPanel panellog2 = new JPanel();
        signup = new JButton("Signup");
        panellog2.add(signup);
        signup.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    BufferedReader logs = new BufferedReader(new FileReader("logs.txt"));
                    String line1,line2;
                    boolean existauser = false;
                    if (user2.getText().equals(""))
                        user2.setBorder(BorderFactory.createLineBorder(Color.red));
                    else{
                        user2.setBorder(new EtchedBorder());
                        user2.setBackground(Color.white);
                    }
                    if (password2.getText().equals(""))
                        password2.setBorder(BorderFactory.createLineBorder(Color.red));
                    else{
                        password2.setBorder(new EtchedBorder());
                        password2.setBackground(Color.white);
                    }
                    if(!user2.getText().equals("") && !password2.getText().equals("")){
                        while((line1=logs.readLine())!=null && (line2=logs.readLine())!=null){
                            if(user2.getText().equals(line1)){
                                existauser = true;
                                JOptionPane.showMessageDialog(logframe, "User-ul exista deja!", "Error", JOptionPane.ERROR_MESSAGE);
                                user2.setText("");
                                password2.setText("");
                                break;
                            }
                        }
                        logs.close();
                        if(existauser == false){
                            BufferedWriter out = new BufferedWriter(new FileWriter("logs.txt",true));
                            out.append(user2.getText());
                            out.newLine();
                            out.append(password2.getText());
                            out.newLine();
                            out.close();
                            JOptionPane.showMessageDialog(logframe, "         User creat!");
                            tabbedpane.setSelectedComponent(tab1);
                            user2.setText("");
                            password2.setText("");
                        }
                    }
                    
                } catch (FileNotFoundException ex) {
                    Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
                } catch (IOException ex) {
                    Logger.getLogger(Interfata.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        panelbuttons2.add(panellog2);
        panelbuttons2.setLayout(new GridLayout(1,1));
        tab2.setBorder(new EmptyBorder(20,10,0,10));
        tab2.add(panelbuttons2);
        
        tabbedpane.addTab("Sign Up", tab2);
        
        logframe.add(tabbedpane);
        
        logframe.pack();
    }
    
    public static void indexWindow(){
        index = new JFrame("Index");
        index.setLayout(new GridLayout(2,1));
        initWindow(index);
        
        JLabel indexlabelmessage = new JLabel("Alegeti optiunea:");
        JPanel indexpanelmessage = new JPanel();
        indexpanelmessage.add(indexlabelmessage);
        index.add(indexpanelmessage);
        
        JPanel indexpanelbuttons = new JPanel();
        index.add(indexpanelbuttons);
        b1 = new JButton("Incarcare fisiere");
        b2 = new JButton("Administrare produse");
        b3 = new JButton("Statistica");
        indexpanelbuttons.add(b1);
        indexpanelbuttons.add(b2);
        indexpanelbuttons.add(b3);
        b1.addActionListener(new action());
        b2.addActionListener(new action());
        b3.addActionListener(new action());
        indexpanelbuttons.setBorder(new EmptyBorder(5,5,5,5));
        
        index.pack();
    }
    
    public static void main(String[] args) {
        logWindow();
    }
}