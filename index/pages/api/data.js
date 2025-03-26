let latestData = { flow: 0, total: 0 };

export default function handler(req, res) {
  if (req.method === 'GET') {
    console.log('📤 Serving the latest data:', latestData);
    res.status(200).json(latestData);
  } else {
    res.status(405).json({ message: 'Only GET allowed' });
  }
}

export { latestData };
