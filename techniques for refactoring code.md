## techniques for refactoring code

Here are some common techniques for refactoring code in English:

### **Extract Method**: 

Identify a block of code 

that can be extracted into 

its own method or function, 

making the original code 

more readable and reusable.

### **Inline Method**: 

If a method is simple 

and is only called once, 

it can be inlined into the calling code, 

reducing complexity.



Here's an example of the "Inline Method" refactoring technique in English:

Original Code:
```c++
class Order {
    private int quantity;
    private double unitPrice;

    public double getTotal() {
        return calculateTotal();
    }

    private double calculateTotal() {
        return quantity * unitPrice;
    }
}
```

Refactored Code:
```c++
class Order {
    private int quantity;
    private double unitPrice;

    public double getTotal() {
        return quantity * unitPrice;
    }
}
```

In the original code, the `getTotal()` method simply calls the `calculateTotal()` method, which performs the actual calculation. This is an unnecessary abstraction, as the calculation is straightforward and the `calculateTotal()` method is only called once.

By applying the "Inline Method" technique, we can remove the `calculateTotal()` method and inline the calculation directly into the `getTotal()` method. This makes the code more concise and easier to read, as there is no unnecessary indirection.

The key benefits of this refactoring are:

1. **Simplicity**: The code is more straightforward and easier to understand, as there is no separate method to call.
2. **Efficiency**: Removing the method call can improve the runtime performance of the code, especially in performance-critical parts of the application.
3. **Maintainability**: With fewer methods, there is less code to maintain and update, reducing the risk of introducing bugs.

By applying this and other refactoring techniques, you can improve the overall quality and readability of your codebase.

### **Rename Variable/Method/Class**: 

Improve the names of 

variables, methods, and classes 

to better reflect their purpose 

and make the code 

more self-documenting.

### **Move Method/Field**: 

If a method or field 

is more closely related 

to another class, 

move it to that class 

to improve cohesion.

### **Introduce Parameter Object**: 

If a method takes multiple related parameters, 

create a new object 

to hold those parameters, 

simplifying the method signature.

### **Encapsulate Field**: 

Make fields private 

and provide public getter and setter methods 

to control access 

and hide implementation details.

### **Decompose Conditional**: 

Break down 

complex conditional statements 

into smaller, more understandable parts.

### **Consolidate Conditional Expression**: 

Combine 

multiple if-statements that check the same condition 

into a single conditional expression.

Sure, here's an example of how you can use the "Consolidate Conditional Expression" refactoring technique:

Original Code:
```java
class Discount {
    private int quantity;
    private double unitPrice;

    public double getDiscountedPrice() {
        double discountedPrice = unitPrice;
        if (quantity > 100) {
            discountedPrice *= 0.9;
        }
        if (unitPrice > 50.0) {
            discountedPrice *= 0.8;
        }
        return discountedPrice;
    }
}
```

Refactored Code:
```java
class Discount {
    private int quantity;
    private double unitPrice;

    public double getDiscountedPrice() {
        double discountedPrice = unitPrice;
        discountedPrice *= getQuantityDiscount() * getPriceDiscount();
        return discountedPrice;
    }

    private double getQuantityDiscount() {
        return (quantity > 100) ? 0.9 : 1.0;
    }

    private double getPriceDiscount() {
        return (unitPrice > 50.0) ? 0.8 : 1.0;
    }
}
```



In the original code, the `getDiscountedPrice()` method contains two separate `if` statements that check the `quantity` and `unitPrice` conditions and apply the corresponding discounts. 

This can be consolidated into a single conditional expression using the ternary operator `?:`.

By applying the "Consolidate Conditional Expression" refactoring, we've extracted the discount calculation logic into two private methods, `getQuantityDiscount()` and `getPriceDiscount()`. 

These methods encapsulate the conditional logic 

and return the appropriate discount factor 

based on the given conditions.

The benefits of this refactoring are:

1. **Readability**: The `getDiscountedPrice()` method is now more concise and easier to understand, as the conditional logic is separated into smaller, more focused methods.
2. **Maintainability**: If the discount calculation rules change in the future, you only need to update the logic in the `getQuantityDiscount()` and `getPriceDiscount()` methods, without having to modify the `getDiscountedPrice()` method.
3. **Reusability**: The `getQuantityDiscount()` and `getPriceDiscount()` methods can be reused in other parts of the application, if needed.

This refactoring technique is particularly useful when you have multiple `if` statements that check the same condition and apply different logic based on that condition. By consolidating the conditional expressions, you can improve the overall code quality and make it easier to maintain and extend in the future.

### **Replace Temp with Query**: 

If a temporary variable 

is used to hold the result of an expression, 

replace it with a method that returns the result of the expression.



The "Replace Temp with Query" refactoring technique is used to replace a temporary variable with a method that calculates the value of the temporary variable.

Here's an example:

Original Code:
```java
class Order {
    private double price;
    private int quantity;

    public double getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }

    public double getTotal() {
        double basePrice = price * quantity;
        double discountAmount = Math.max(0, basePrice - 100);
        return basePrice - discountAmount;
    }
}
```

Refactored Code:
```java
class Order {
    private double price;
    private int quantity;

    public double getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }

    public double getTotal() {
        return getBasePrice() - getDiscountAmount();
    }

    private double getBasePrice() {
        return price * quantity;
    }

    private double getDiscountAmount() {
        return Math.max(0, getBasePrice() - 100);
    }
}
```



In the original code, the `getTotal()` method uses two temporary variables, `basePrice` and `discountAmount`, to perform the calculation. By applying the "Replace Temp with Query" refactoring  technique, we can replace these temporary variables with private methods `getBasePrice()` and `getDiscountAmount()` that encapsulate the calculation logic.

The benefits of this refactoring are:

1. **Readability**: The `getTotal()` method becomes more expressive and easier to understand, as it uses meaningful method names to describe the calculation steps.
2. **Reusability**: The `getBasePrice()` and `getDiscountAmount()` methods can be reused in other parts of the application, if needed.
3. **Testability**: The calculation logic in the private methods can be tested independently, making it easier to ensure the correctness of the overall calculation.

By applying this refactoring technique, you can improve the overall code quality and maintainability of your application, especially when dealing with complex calculations or expressions.

### **Introduce Explaining Variable**: 

Replace a complex expression with a variable 

that explains the purpose of the expression.

Sure, here's an example of how you can use the "Introduce Explaining Variable" refactoring technique:

Original Code:
```java
class ShippingCalculator {
    public double calculateShippingCost(double weight, double distance) {
        return (weight > 10.0) ? (distance * 1.2) : (distance * 0.5);
    }
}
```

Refactored Code:
```java
class ShippingCalculator {
    public double calculateShippingCost(double weight, double distance) {
        double ratePerMile = (weight > 10.0) ? 1.2 : 0.5;
        return distance * ratePerMile;
    }
}
```

In the original code, the `calculateShippingCost()` method uses a ternary operator to determine the rate per mile based on the weight of the package. While the code is relatively straightforward, the purpose of the expression `(weight > 10.0) ? (distance * 1.2) : (distance * 0.5)` might not be immediately clear to someone unfamiliar with the domain.

By applying the "Introduce Explaining Variable" refactoring, we've extracted the rate per mile calculation into a variable called `ratePerMile`. This variable serves as an explaining variable, making the purpose of the expression more explicit and easier to understand.

The benefits of this refactoring are:

1. **Readability**: The `calculateShippingCost()` method is now more self-documenting, as the purpose of the rate per mile calculation is clearly expressed through the `ratePerMile` variable.
2. **Maintainability**: If the logic for calculating the rate per mile changes in the future, you only need to update the calculation in the `ratePerMile` variable, without having to modify the overall `calculateShippingCost()` method.
3. **Testability**: The `ratePerMile` variable can be easily tested in isolation, which can improve the overall testability of the code.

This refactoring technique is particularly useful when you have complex expressions that are difficult to understand or when the purpose of an expression is not immediately clear. By introducing an explaining variable, you can improve the code's readability and make it easier to maintain and understand in the long run.

### **Split Temporary Variable**: 

If a variable is used for two unrelated purposes, 

split it into two separate variables.

Certainly! Here's an example of how you can apply the "Split Temporary Variable" refactoring technique:

Original Code:
```java
class InventoryReporter {
    public void generateReport(List<Item> items) {
        double totalValue = 0.0;
        int numItems = 0;
        for (Item item : items) {
            totalValue += item.getPrice();
            numItems++;
        }
        double averageValue = totalValue / numItems;
        System.out.println("Total value: $" + totalValue);
        System.out.println("Average value: $" + averageValue);
    }
}
```

Refactored Code:
```java
class InventoryReporter {
    public void generateReport(List<Item> items) {
        double totalValue = calculateTotalValue(items);
        int numItems = countItems(items);
        double averageValue = calculateAverageValue(totalValue, numItems);
        System.out.println("Total value: $" + totalValue);
        System.out.println("Average value: $" + averageValue);
    }

    private double calculateTotalValue(List<Item> items) {
        double totalValue = 0.0;
        for (Item item : items) {
            totalValue += item.getPrice();
        }
        return totalValue;
    }

    private int countItems(List<Item> items) {
        int numItems = 0;
        for (Item item : items) {
            numItems++;
        }
        return numItems;
    }

    private double calculateAverageValue(double totalValue, int numItems) {
        return totalValue / numItems;
    }
}
```

In the original code, the `generateReport()` method uses a single variable `totalValue` to keep track of both the total value of all items and the average value per item. This can lead to confusion and make the code harder to maintain, as the purpose of the `totalValue` variable is not immediately clear.

By applying the "Split Temporary Variable" refactoring, we've split the `totalValue` variable into two separate variables: `totalValue` and `numItems`. We've also extracted the calculation of the total value, item count, and average value into separate private methods, making the code more modular and easier to understand.

The benefits of this refactoring are:

1. **Readability**: The purpose of each variable is now clearly defined, making the code more self-documenting.
2. **Maintainability**: If the logic for calculating the total value, item count, or average value changes in the future, you only need to update the corresponding private method, without having to modify the `generateReport()` method.
3. **Testability**: The private methods can be easily tested in isolation, which can improve the overall testability of the code.

This refactoring technique is particularly useful when a variable is used for multiple, unrelated purposes. By splitting the variable into separate, explaining variables, you can improve the code's readability, maintainability, and testability.

### **Remove Dead Code**: 

Identify and remove any unused

 code, variables, or methods.



By applying these and other refactoring techniques, you can improve the structure, readability, and maintainability of your code.