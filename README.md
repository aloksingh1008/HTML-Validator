HTML Validator in C++
Purpose:
The HTML Validator is a C++ program designed to parse HTML code, extract information about various HTML elements (tags), and perform validation checks based on specific criteria.

Components:

  TagInfo Structure:

  The TagInfo structure represents information about an HTML tag. It contains members such as tagName, id, classes, text, href, target, and children.
    tagName: Stores the name of the HTML tag (e.g., "div", "a", "h1").
    id: Stores the ID attribute of the tag, if present.
    classes: Stores a set of class names associated with the tag, if present.
    text: Stores the text content within the tag.
    href: Stores the value of the "href" attribute for anchor tags (<a>).
    target: Stores the value of the "target" attribute for anchor tags.
    children: Stores pointers to child tags of the current tag.


  Utility Functions:

    ltrim, rtrim, and trim: These functions are used to trim leading and trailing whitespace characters from a string.
    extractHREF, extractTarget, extractID, extractClasses, extractTagName, and extractText: These functions are used to extract specific attributes (such as href, target,         id, classes, tag name, and text content) from a string representing an HTML tag.
    
    
  Parsing HTML Code:
  
    The extractCode function parses the HTML code line by line from standard input.
      It identifies opening tags, closing tags, and self-closing tags, and constructs a tree-like structure representing the hierarchy of HTML elements.
      It populates instances of the TagInfo structure with information about each tag.


  Validation Checks:

  The validation function recursively traverses the tag tree and performs validation checks based on specific criteria.
  It checks for the presence of certain attributes (e.g., "id", "href"), and content (e.g., text within <h1> tags).
  Validation checks are performed by updating a vector checks with binary values (1 for pass, 0 for fail) corresponding to each criterion.


Main Function:

  The main function orchestrates the overall execution of the program.
  It initializes variables, sets up input/output redirection, invokes the HTML parsing and validation functions, and outputs the results of validation checks.
  How to Use:
    1. Prepare an HTML file to be validated.
    2. Redirect the input of the program to read from the HTML file.
    3. Run the program.
    4. Check the output to see the results of the validation checks.

  Example:
    Suppose we have an HTML file with various elements such as <h1>, <a>, <div>, etc. The program will parse the HTML code, extract information about each tag, and perform       validation checks based on specific criteria defined in the code.

  Limitations and Considerations:
    1. The program assumes well-formed HTML code and may not handle all edge cases or malformed HTML gracefully.
    2. Validation criteria are predefined in the code and may need to be adjusted based on specific requirements or standards.
