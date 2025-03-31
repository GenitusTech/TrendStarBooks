package com.trendstarbooks;

import org.checkerframework.checker.tainting.qual.Untainted;

/**
 * Hello world!
 *
 */
public class App {
  public static void main(@Untainted String[] args) {
    System.out.println("Hello World!");
  }
}
