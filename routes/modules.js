const express = require('express');
const router = express.Router();

router.get('/', (req, res, next) => {
    res.status(200).json({
        message : "Handling requests with GET method"
    })
});

router.post('/', (req, res, next) => {
    const moduledata = {
      moduleId: req.body.moduleId
    }
    res.status(200).json({
        message : "Handling requests with POST method",
        modules : moduledata
    })
});

router.get('/:moduleId', (req, res, next) =>{
    const id = req.params.moduleId;
    if(id === 'special'){
        res.status(200).json({
            message : "You Entered a special id"
        })
    }
    else{
        res.status(200).json({
            message : "You Entered a ID"
        })
    }
});

module.exports = router;