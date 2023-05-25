//
// Created by murph on 17.05.23.
//

#ifndef INC_05_HOMEWORK_DMODEL_H
#define INC_05_HOMEWORK_DMODEL_H

#include "gModel.h"
#include "doc.h"

class dModel {
public:
    dModel() = delete;

    explicit dModel(const std::shared_ptr<gModel>& gr_mdl) :
            graphics_model(gr_mdl), current_document(nullptr), last_number(1) {}

    ~dModel() = default;

    void create_document();

    void import_document_from_file(const std::string& file_path);

    void export_document_to_file(const std::string& doc_id, const std::string& file_path);

    void export_document(const std::string& doc_id);

    void close_document(const std::string& doc_id);

    std::vector<std::shared_ptr<Document>> get_all_documents() {
        return documents;
    }

    std::shared_ptr<Document> get_current_document() {
        return current_document;
    }

    void clear() {
        documents.clear();
    }

    void output_info();

    void update();

private:
    std::shared_ptr<gModel> graphics_model; // Äëÿ ñâÿçè ñ ìîäåëüþ ñ ãðàôè÷åñêèìè îáúåêòàìè.

    std::shared_ptr<Document> current_document; // Òåêóùèé äîêóìåíò.

    uint32_t last_number; // Äëÿ ãåíåðàöèè óíèêàëüíîãî èäåíòèôèêàòîðà äîêóìåíòà.

    std::vector<std::shared_ptr<Document>> documents; // Êîëëåêöèÿ äîêóìåíòîâ â ìîäåëè.

    std::string current_file; // Ôàéë, â êîòîðûé ýêñïîðòèðîâàëè ïðîøëûé ðàç.


};



#endif //INC_05_HOMEWORK_DMODEL_H
