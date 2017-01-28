
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Stefan
 */
public class Cell {
    
    private boolean[] domain;
    private int row, column, value, domainSize;
    
    
    public Cell(int row, int column) {
        this.value = 0;
        this.row = row;
        this.column = column;
        domain = new boolean[9];
        Arrays.fill(domain, true);
        domainSize = 9;
    }
    
    public Cell(int row, int column, int value) {
        this.value = value;
        this.row = row;
        this.column = column;
        domain = new boolean[9];
        Arrays.fill(domain, false);
        domain[value - 1] = true;
        domainSize = 1;
    }

    /**
     * @return the row
     */
    public int getRow() {
        return row;
    }

    /**
     * @return the column
     */
    public int getColumn() {
        return column;
    }

    /**
     * @return the value
     */
    public int getValue() {
        return value;
    }

    /**
     * @param value the value to set
     */
    public void setValue(int value) {
        this.value = value;
        Arrays.fill(domain, false);
        domain[value - 1] = true;
        domainSize = 1;
    }

    /**
     * @return the domainSize
     */
    public int getDomainSize() {
        return domainSize;
    }
    
    public void removeFromDomain(int value) {
        if (domain[value - 1]) {
            domain[value - 1] = false;
            domainSize --;
        }
    }
    
    public List<Integer> getPossibleValues() {
        List<Integer> result = new LinkedList<Integer>();
        for (int i = 0; i < 9; i++)
            if (domain[i]) result.add(i + 1);
        return result;
    }
    
    @Override
    public Object clone() {
        Cell cell;
        if (value == 0) cell = new Cell(row, column);
        else cell = new Cell(row, column, value);
        cell.domain = Arrays.copyOf(domain, 9);
        cell.domainSize = domainSize;
        return cell;
    }
    
    
}
