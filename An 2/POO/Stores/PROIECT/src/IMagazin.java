public interface IMagazin {
    public double getTotalFaraTaxe();
    public double getTotalCuTaxe();
    public double getTotalCuTaxeScutite();
    public double getTotalTaraFaraTaxe(String name);
    public double getTotalTaraCuTaxe(String name);
    public double getTotalTaraCuTaxeScutite(String name);
    public double calculScutiriTaxe();
    public double calculScutiriTaxeTara(String name);
}
