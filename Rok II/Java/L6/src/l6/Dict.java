/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package l6;

/**
 * Interfejs do operacji na BST
 * @author KrystianGrabowski
 */
public interface Dict<T extends Comparable<T>> {
   /**
    * Wyszukuje i zwaraca wartosc szukanego elementu
    * @param elem element do znalezienia
    * @return szukany element
    */
    public T search(T elem);
    
    /**
     * Wstawia podany element do naszego zbioru
     * @param elem element do dodania 
     */
    public void insert(T elem) throws NullPointerException;
    
    /**
     * Usuwa podany element z naszego zbioru
     * @param elem  element do usunęcia
     */
    public void remove(T elem);
    
    /**
     * Wyszukuje i zwraca najmniejszy element z naszego zbioru
     * @return minimim spośród elementów zbioru
     */
    public T min();
    
    /**
     * Wyszukuje i zwraca największy element z naszego zbioru
     * @return maksimum spośród elementów zbioru
     */
    public T max();
    
    
       
}
