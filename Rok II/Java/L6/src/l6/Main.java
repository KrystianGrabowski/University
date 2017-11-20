/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package l6;

/**
 *
 * @author krystian
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("Hello World");
        BST tree = new BST();
        tree.insert(8);
        tree.insert(3);
        tree.insert(1);
        tree.insert(6);
        tree.insert(4);
        tree.insert(7);
        tree.insert(10);
        tree.insert(14);
        tree.insert(13);
        System.out.println(tree.toString());
        tree.clear();
        System.out.println(tree.toString());


    }
    
}
