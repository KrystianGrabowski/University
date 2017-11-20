
package l6;

import algorithms.BST;

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
        tree.remove(8);
        System.out.println(tree.search(8));
        System.out.println(tree.toString());

        BST StringTree = new BST();
        StringTree.insert("ccc");
        StringTree.insert("bbb");
        StringTree.insert("aaa");
        StringTree.insert("eeeee");
        StringTree.insert("zzzzzzzzzz");
        System.out.println(StringTree.toString());
        StringTree.remove("aaa");
        System.out.println(StringTree.search("aaa"));
        System.out.println(StringTree.toString());

        

    }
    
}
