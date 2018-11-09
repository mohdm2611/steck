const express = require('express');
const router = express.Router();
const mongoose = require('mongoose');

const Moduledata = require('../models/module');

router.get('/', (req, res, next) => {   
    Moduledata.find()
    .select('mappedTo type status')
    .exec()
    .then(docs => {
        const response = {
            count: docs.length,
            modules: docs.map(doc => {
                return {
                    mappedTo: doc.mappedTo,
                    type: doc.type,
                    status: doc.status,
                    id: doc._id,
                    request: {
                        type: 'GET',
                        url: 'http://localhost:8000/modules/' + doc._id
                    }
                }
            })
        }
        res.status(200).json(response);
    })
    .catch(err => {
        console.log(err);
        res.status(500).json({error: err});
    });
});

router.post('/', (req, res, next) => {
    const moduledata = new Moduledata({
        _id: new mongoose.Types.ObjectId(),
        mappedTo: req.body.mappedTo,
        type: req.body.type,
        status: req.body.status
    });
    moduledata.save()
    .then(result => {
        console.log(result);
        res.status(201).json({
            message : "Created module",
            modules : {
                mappedTo: result.mappedTo,
                type: result.type,
                status: result.status,
                id: result._id,
                request: {
                    type: 'GET',
                    url: 'http://localhost:8000/modules/' + result._id
                }
            }
        });
    }).catch(err => {
        console.log(err);
        res.status(500).json({error: err});
    });
    
});

router.get('/:moduleId', (req, res, next) =>{
    const id = req.params.moduleId;
    Moduledata.findById(id)
    .exec()
    .then(doc =>{
        console.log("From database"+doc);
        if(doc){
            res.status(200).json(doc);
        }
        else{
            res.status(404).json({message: 'No Valid Entry Found'});    
        }
    })
    .catch(err => {
        console.log(err);
        res.status(500).json({error: err});
    })
});

router.patch('/:moduleId', (req, res, next) => {
    const id = req.params.moduleId;
    const updateops = {};
    for(const ops of req.body){
        updateops[ops.propName] = ops.value;
    }
    Moduledata.update({ _id: id}, { $set: updateops })
    .exec()
    .then(result => {
        console.log(result);
        res.status(200).json({result});
    })
    .catch(err => {
        console.log(err);
        res.status(500).json({error: err});
    })
})

router.delete('/:moduleId', (req, res, next) => {
    const id = req.params.moduleId;
    Moduledata.remove({ _id: id}).exec()
    .then(result => {
        res.status(200).json({result});
    })
    .catch(err => {
        console.log(err);
        res.status(500).json({error: err});
    });
}); 

module.exports = router;
