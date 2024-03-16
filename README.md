# HTML Validation Tool Documentation

## Introduction

The HTML Validation Tool is a C++ program designed to analyze HTML code and perform validation checks on its structure and attributes. The tool processes the HTML code, builds a tree structure representing the hierarchy of HTML tags, and checks for the presence of specific elements and attributes according to predefined validation criteria.

## Features

- **Parsing HTML**: The tool parses HTML code to identify and extract information about HTML tags, including tag names, attributes, and text content.
- **Building Tag Tree**: The program builds a tree structure to represent the hierarchy of HTML tags, with each node in the tree representing an HTML tag and its attributes.
- **Validation Checks**: Various validation checks are performed on the HTML code, including:
  - Presence of specific sections (e.g., "Welcome" section, "Projects" section).
  - Structure of HTML elements (e.g., presence of h1 tags within specific sections).
  - Attributes of HTML elements (e.g., presence of specific IDs, classes, href attributes).
- **Output Results**: After processing the HTML code and performing validation checks, the tool outputs the results of these checks, indicating whether each check passed or failed.

## Components

The HTML Validation Tool consists of the following components:

1. **Main Program**: The main program is responsible for coordinating the overall process, including reading input, parsing HTML code, performing validation checks, and outputting results.

2. **HTML Tag Structure**: The program defines a structure `TagInfo` to represent information about HTML tags. This structure includes members such as tag name, classes, ID, text content, and child tags.

3. **Remove Comments**: The Program first remove all comments in the file.

4. **Parsing Functions**: Functions are provided to parse HTML code and extract **multilined** information about tags, attributes, and text content. These functions handle the extraction of tag names, IDs, classes, href attributes, and text content.

5. **Validation Functions**: Validation functions are implemented to perform specific checks on the structure and attributes of HTML elements. These functions analyze the tag tree and attribute values to determine if the HTML code meets the validation criteria.

6. **String Searching Algorithms**: The program utilizes the Knuth-Morris-Pratt (KMP) string searching algorithm to efficiently search for specific patterns within strings.

## Usage

1. **Input**: The HTML code to be validated is provided as input to the program. This input can be read from a file or entered interactively.

2. **Processing**: The program processes the HTML code, parses it to build a tag tree, and performs validation checks according to predefined criteria.

3. **Output**: The results of the validation checks are outputted, indicating whether each validation criterion passed or failed. Additionally, any errors or warnings encountered during processing are reported.

## Dependencies

The HTML Validation Tool requires the following dependencies:

- Standard C++ libraries (`<iostream>`, `<string>`, `<vector>`, `<sstream>`, `<set>`)
- Knuth-Morris-Pratt (KMP) string searching algorithm implementation

## Conclusion

The HTML Validation Tool provides a robust solution for analyzing and validating HTML code. By parsing HTML, building a tag tree, and performing validation checks, the tool ensures that HTML documents adhere to specified structural and attribute requirements.
