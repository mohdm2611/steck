const accountSid = 'AC66dead53c973552acb3620dce467cdb9';
const authToken = 'c45a57ff20582c121a6bd1a2f2df7673';
const client = require('twilio')(accountSid, authToken);

client.messages
  .create({
     body: 'The location of the manhole is at maps.google.com',
     from: '+15312081934',
     to: '+918686427332'
   })
  .then(message => console.log(message.sid))
  .done();