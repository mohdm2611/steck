const mongoose = require('mongoose');

const modulesSchema = mongoose.Schema({
    _id: mongoose.Schema.Types.ObjectId, 
    mappedTo: { type: String, required: true },
    type: { type: String, required: true },
    status: { type: String, required: true }
});

module.exports = mongoose.model('Moduledata', modulesSchema);