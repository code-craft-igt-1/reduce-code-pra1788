# Reduce code for a smooth read

Objective of this assignment is to reduce the amount of code that a maintainer has to read.

## What's been done

The image brightener now has two features:
1. Brighten the whole image by adding a constant grayscale value to each pixel
2. Add a brightening image, so we can supply a different grayscale addition for each pixel. E.g., an x-ray of the abdomen can be dark in the middle, so we may want to brighten only that part

However, there is duplication of code and lack of encapsulation. Static analysis reflects this as well. See output of the workflows.

## Your task - refactor and reduce code

**Part 1**: Refactor the code to remove duplication and reduce complexity.

Hint: Create a method called `processPixels` in the `Image` class. Move the iteration (for loops) into it.
However, the for loop needs to invoke the processing code. But let's not make the `Image` class take up all the processing. Hence, inject the processing logic into the `Image` class.

There are different ways to do this:

- Create a base class called `IPixelProcessor`, with a pure-virtual function to do the processing. Derive two brighteners from it. Make `processPixels` accept a reference to `IPixelProcessor`

or, reduce the amount of code:

- Accept a function in `processPixels`. Use lambdas with capture groups in the caller, one for each brightener.

**Part 2**: Fix the test-failure due to a bug in `AddBrighteningImage`.

While fixing the bug, also look at ways in which the mistake can be caught at compile time itself.
