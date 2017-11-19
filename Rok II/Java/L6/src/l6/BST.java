/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package l6;

/**
 *
 * @author KrystianGrabowski
 * @param <T> tsd
 */
public class BST<T extends Comparable<T>> implements Dict<T> {
   
    private class Node <T extends Comparable<T>> {
        Node <T> left;
        Node <T> right;
        Node <T> parent;
        T data;
        
        public Node(){
           right = null;
           left = null;
           parent = null;
           data = null;
                   
        }
    }
    
    public Node<T> root;

    int size;
    public BST(){
        root = new Node<T>();
        size = 0;
        root.parent = root;
    }
    
    @Override
    public void insert(T elem) throws NullPointerException{
        if (elem == null){
            throw new NullPointerException("parametr ma wartość null");
        }
        
        Node InsertNode = new Node<T>();
        InsertNode.data = elem;
        
        if (size() == 0){
            root = InsertNode;
        }
        else{
        
        Node temp = root;
        Node parenttemp = null;
        
        while(temp != null){
            parenttemp = temp;
            if(InsertNode.data.compareTo(temp.data) < 0){
                temp = temp.left;
            }
            else{
                temp = temp.right;
            }
        }
        InsertNode.parent = parenttemp;
        if (InsertNode.data.compareTo(parenttemp.data) < 0){
            parenttemp.left = InsertNode;
        }
        else{
            parenttemp.right = InsertNode;
        }
        }
        size += 1;
    }
    
    
    @Override
    public T search(T elem) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void remove(T elem) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public T min() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public T max() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    public int size(){
        return size;
    }
    
    public String toString(){
        return toString2(new StringBuilder(), root).toString();
    }
    
    public StringBuilder toString2(StringBuilder result, Node temp){
        if(temp == null) return result;
        toString2(result,temp.left);
        result.append(temp.data);
        result.append(" ");
        toString2(result,temp.right);
        return result;
        

    }
}
