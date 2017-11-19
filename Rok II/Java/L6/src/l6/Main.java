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
        tree.insert(20);
        tree.insert(10);
        tree.insert(30);
        tree.insert(15);
        tree.insert(21);



        System.out.println(tree.toString());
    }
    
}
