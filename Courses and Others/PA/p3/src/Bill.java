public class Bill {
    private static final int MOD = 9901;
    private static final int MAX_TERM = 19;

    private int N;
    private int R;

    public Bill(int N, int R) {
        this.N = N;
        this.R = R;
    }

    private int countSols() {
        int[][] count = new int[N + 1][100];

        //count[i][j] = cate sume exista care au i termeni si care dau restul j
        //la impartirea prin 100

        //TODO Initializati linia 1 a dinamicii
        for (int t = 0; t <= MAX_TERM; ++t) {
            count[1][t] = 1;
        }

        //TODO Calculati liniile 2..N ale dinamicii
        //Pentru a determina numarul de sume cu i termeni puteti considera ca
        //mai adaugati un termen la sumele care au (i - 1) termeni
        for (int i = 2; i <= N; ++i) {
            for(int j = 0; j < 100; j++){
            	int suma = 0;
            	for(int k = 0; k < 20; k++)
            		suma = (suma + count[i-1][(100-k+j) % 100]) % 9901;
            	count[i][j] = suma;
            }
        }

        return count[N][R];
    }

    //Inmulteste matricele A si B. Operatiile sunt modulo MOD.
    private int[][] multiplyMatrix(int[][] A, int[][] B) {
        final int N = A.length;
        final int M = B[0].length;
        final int K = A[0].length;

        int[][] Res = new int[N][M];

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < K; ++k) {
                    Res[i][j] = (Res[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }

        return Res;
    }

    //Inmulteste matricea A cu vectorul v. Operatiile sunt modulo MOD
    private int[] multiplyMatrixVector(int[][] A, int[] v) {
        final int N = A.length;
        final int M = v.length;

        int[] vRes = new int[N];

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                vRes[i] = (vRes[i] + A[i][j] * v[j]) % MOD;
            }
        }

        return vRes;
    }

    //Ridica la puterea p matricea patratica A. Operatiile sunt modulo MOD.
    private int[][] logPowMatrix(int[][] A, int p) {
        int[][] Res = new int[A.length][A.length];

        for (int i = 0; i < Res.length; ++i) {
            Res[i][i] = 1;
        }

        //TODO
        //Caculati Res = pow(A, p)
        

        return Res;
    }

    private int countSolsLog() {
        int[][] A = new int[100][100];
        int[] count = new int[100];

        //TODO Initializati count.
        //count[i] = cate sume cu un termen dau restul i la impartirea prin 100
        for (int t = 0; t <= MAX_TERM; ++t) {
            
        }

        //TODO Initializati matricea A
        //Hint: vreti ca (A * count) sa fie un vector in care elementul i sa
        //reprezinte numarul de moduri in care putem construi secvente cu N
        //termeni a caror suma sa dea restul i la impartirea prin 100
        

        //TODO Ridicati matricea A la putere folosind functia logPowMatrix
        //Faceti acest lucru dupa ce ati completat functia logPowMatrix
        

        count = multiplyMatrixVector(A, count);

        return count[R];
    }

    public static void main(String[] args) {
        Input[] inputs = {
            new Input(3, 2), // 6
            new Input(123, 4), // 2490
            new Input(2014, 3) // 244
        };

        for (Input input : inputs) {
            Bill bill = new Bill(input.N, input.R);

            System.out.print("N = " + input.N + ", ");
            System.out.print("R = " + input.R + " -> ");
            System.out.print(bill.countSols());
            System.out.print(" ");
            System.out.print(bill.countSolsLog());
            System.out.println();
        }
    }

    private static class Input {
        public int N;
        public int R;

        Input(int N, int R) {
            this.N = N;
            this.R = R;
        }
    }
}
