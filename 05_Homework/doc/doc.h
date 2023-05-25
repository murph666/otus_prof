//
// Created by murph on 22.05.23.
//

#ifndef INC_05_HOMEWORK_DOC_H
#define INC_05_HOMEWORK_DOC_H

#include <string>
#include <memory>
#include <vector>
#include "fig.h"

class Document {
    using shared_document = std::shared_ptr<Document>;
    using vector_document = std::vector<std::shared_ptr<Document>>;

public:
    Document() : document_id("unknown") {}

    explicit Document(const std::string &doc_id) : document_id(doc_id) {}

    ~Document() = default;

    std::string get_document_id() { return document_id; }

    void add_figure(const std::shared_ptr<Figure>& figure_ptr) {
        graphic_objects.push_back(figure_ptr);
    }

    void clear() {
        graphic_objects.clear();
    }

private:
    std::string document_id;
    std::vector<std::shared_ptr<Figure>> graphic_objects;
};

#endif //INC_05_HOMEWORK_DOC_H
