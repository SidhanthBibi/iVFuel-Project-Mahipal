// index/api/update.js

export async function POST(req) {
    try {
      const url = process.env.KV_REST_API_URL;
      const token = process.env.KV_REST_API_TOKEN;
  
      const { flow, total } = await req.json();
  
      const response = await fetch(`${url}/set/latest`, {
        method: "POST",
        headers: {
          Authorization: `Bearer ${token}`,
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ flow, total }),
      });
  
      if (!response.ok) {
        return new Response("Failed to update", { status: 500 });
      }
  
      return new Response("Stored successfully", { status: 200 });
    } catch (err) {
      console.error("POST /api/update error:", err);
      return new Response("Internal server error", { status: 500 });
    }
  }
  