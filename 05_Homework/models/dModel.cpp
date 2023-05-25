//
// Created by murph on 17.05.23.
//

#include "dModel.h"

#include <iostream>

void dModel::create_document()
{
    std::string doc_id = "doc_" + std::to_string(last_number);
    last_number++;

    shared_document new_doc = std::make_shared<Document>(doc_id);

    documents.push_back(new_doc);
    current_document = documents.back();

    std::cout << "\nNew document with id " << doc_id << " has been created" << std::endl;

    notify();
}

void dModel::import_document_from_file(const std::string& file_path)
{
    /*
    * Íåêèé êîä ñ îòêðûòèåì ôàéëà è äîáàâëåíèåì äîêóìåíòà â êîëëåêöèþ.
    */

    std::cout << "Document has been imported from file: " << file_path << std::endl;

    notify();
}

void dModel::export_document_to_file(const std::string& doc_id, const std::string& file_path)
{
    /*
    * Áåð¸ì ñîäåðæèìîå ãðàôè÷åñêîé ìîäåëè è çàïèñûâàåì â óêàçàííûé ôàéë.
    */

    // Óêàçàííûé ôàéë óñòàíàâëèâàåì êàê òåêóùèé.
    current_file = file_path;

    std::cout << "Document with id: " << doc_id << " has been exported to file : " << file_path << std::endl;
}

void dModel::export_document(const std::string& doc_id)
{
    if (current_file.empty()) {
        return;
    }

    std::cout << "Document with id: " << doc_id << " has been exported to file : " << current_file << std::endl;
}

void dModel::close_document(const std::string& doc_id)
{
    std::cout << "Document with id: " << doc_id << " has been closed" << std::endl;

    notify();
}

void dModel::update()
{
    if (current_document == nullptr) {
        return;
    }

}