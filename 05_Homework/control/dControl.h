//
// Created by murph on 26.05.23.
//

#ifndef INC_05_HOMEWORK_DCONTROL_H
#define INC_05_HOMEWORK_DCONTROL_H

#include "dModel.h"
#include "dView.h"

class dControl {

public:
    dControl() = delete;

    explicit dControl(const std::shared_ptr<dModel> &doc_mdl) : documents_model(doc_mdl) {}

    ~dControl() = default;

    void create_document();

    void import_document_from_file(const std::string &file_path);

    void export_document_to_file(const std::string &doc_id, const std::string &file_path);

    void export_document(const std::string &doc_id);

    void close_document(const std::string &doc_id);

    std::shared_ptr<dView> get_view() {
        return documents_view;
    }

private:
    std::shared_ptr<dModel> documents_model;

    std::shared_ptr<dView> documents_view;


};


#endif //INC_05_HOMEWORK_DCONTROL_H
